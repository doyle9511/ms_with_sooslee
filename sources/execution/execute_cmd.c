/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:52:37 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/01 21:57:43 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* execute_builtin:
내장 명령어(cd, echo, env, export, pwd, unset, exit) 확인 및 실행
성공시 0, 실패시 127 반환
*/
int	execute_builtin(t_data *data, t_command *cmd)
{
	int	code;

	code = CMD_NOT_FOUND;
	if (ft_strncmp(cmd->command, "cd", 3) == 0)
		code = cd_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "echo", 5) == 0)
		code = echo_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "env", 4) == 0)
		code = env_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "export", 7) == 0)
		code = export_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
		code = pwd_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "unset", 6) == 0)
		code = unset_builtin(data, cmd->args);
	else if (ft_strncmp(cmd->command, "exit", 5) == 0)
		code = exit_builtin(data, cmd->args);
	return (code);
}

/* execute_sys_bin:
환경변수 실행 경로에서 명령어의 시스템 바이너리 파일을 찾아 실행.
실행 파일 경로를 찾을 수 없으면 127 반환.
*/
static int	execute_sys_bin(t_data *data, t_command *cmd)
{
	if (!cmd->command || cmd->command[0] == '\0')
		return (CMD_NOT_FOUND);
	if (cmd_is_dir(cmd->command))
		return (CMD_NOT_FOUND);
	cmd->path = get_cmd_path(data, cmd->command);//환경변수에서 일치하는 경로 반환
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->args, data->env) == -1)
		errmsg_cmd("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

/* execute_local_bin:
주어진 명령어를 로컬 디렉토리 파일이나 이미 경로가 포함된 bin으로 실행 시도.
존재하지 않는 실행 파일이면 CMD_NOT_FOUND 반환.
*/
static int	execute_local_bin(t_data *data, t_command *cmd)
{
	int	ret;

	ret = check_command_not_found(data, cmd);
	if (ret != 0)
		return (ret);
	if (execve(cmd->command, cmd->args, data->env) == -1)
		return (errmsg_cmd("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}

/* execute_command:
자식 프로세스가 입출력 fd를 설정하고 실행 파일을 검색하여 주어진 명령어 실행 시도.
실행 파일 검색 순서:
	1. 내장 명령어 실행
	2. 시스템 바이너리 명령어 실행
	3. 주어진 명령어 이름 직접 실행 (로컬 bin)
일치하는 내장 명령어나 실행 파일을 찾지 못하면 에러 메시지 출력.
자식은 실행된 프로그램의 종료 코드로 종료하거나, 찾지 못한 경우 1로 종료.

ls -l        # 시스템 바이너리 실행
./script.sh  # 로컬 바이너리 실행
cd /home     # 내장 명령어 실행
*/
int	execute_command(t_data *data, t_command *cmd)
{
	int	code;

	if (!cmd || !cmd->command)
		exit_shell(data, errmsg_cmd("child", NULL,
				"parsing error: no command to execute!", EXIT_FAILURE));
	if (!check_infile_outfile(cmd->io_fds))
		exit_shell(data, EXIT_FAILURE);
	set_pipe_fds(data->cmd, cmd);//해당 명령어의 파이프fd dup()하기
	redirect_io(cmd->io_fds);//표준입출력 dup 백업저장
	close_fds(data->cmd, false);//fd 닫을건 닫고 정리
	if (ft_strchr(cmd->command, '/') == NULL)//빌트인이나 PATH에서 찾을 수 있는 명령어
	{
		code = execute_builtin(data, cmd);//ls나 echo, grep 등
		if (code != CMD_NOT_FOUND)//builtin이 성공적으로 실행됐다면
			exit_shell(data, code);//자식 종료
		code = execute_sys_bin(data, cmd);//(builtin아니면 여기 진행)ls -> /bin/ls
		if (code != CMD_NOT_FOUND)//PATH에서 찾아서 실행했다면
			exit_shell(data, code);//자식 종료 ()
	}// 아래로 넘어가는 경우_1.'/'표함된 상대/절대 경로 경우 / 2. 없는 명령어 / 3. /가 없지만 현재 디렉토리에 있는 실행파일
	code = execute_local_bin(data, cmd);//ls, /user/bin/ls 혹은 ./ls 등 실행
	exit_shell(data, code);//로컬에서조차 찾기 실패했다먼 에러반환후 자식 종료
	return (code);
}
