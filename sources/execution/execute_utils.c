/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:19:31 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/01 22:09:30 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* cmd_is_dir:
명령어가 실행 파일이 아닌 디렉토리인지 확인.
디렉토리면 true, 아니면 false 반환.
*/
bool	cmd_is_dir(char *cmd)
{
	struct stat	cmd_stat;//stat함수를 통해 구조체에 파일정보를 채움

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));//stat구조체를 통해 파일이 디렉토리인지 확인하는 매크로 (디렉토리면 1, 아니면 0)
}

/* check_command_not_found:
시스템 바이너리에서 명령어를 찾지 못한 이유를 검색.
명령어가 유효하지 않으면 에러 메시지와 상태(126 혹은 127) 반환,
로컬 실행파일로 실행해야 하는 유효 명령어면 0 반환.

./directory    # Is a directory
./noexist      # No such file or directory
./nopermission # Permission denied
invalidcmd     # command not found
*/
int	check_command_not_found(t_data *data, t_command *cmd)
{
	if (ft_strchr(cmd->command, '/') == NULL// '/'가 없고 PATH환경변수가 있는 경우
		&& get_env_var_index(data->env, "PATH") != -1)// (PATH도 있고, '/'도 없는데 여기까지 왔다? -> 이미 검색실패)
		return (errmsg_cmd(cmd->command, NULL, "command not found",
				CMD_NOT_FOUND));
	if (access(cmd->command, F_OK) != 0)//파일이 존재하지 않는 경우
		return (errmsg_cmd(cmd->command, NULL, strerror(errno), CMD_NOT_FOUND));
	else if (cmd_is_dir(cmd->command))//디렉토리인 경우
		return (errmsg_cmd(cmd->command, NULL, "Is a directory",
				CMD_NOT_EXECUTABLE));
	else if (access(cmd->command, F_OK | X_OK) != 0)//파일은 존재하지만 실행권한이 없는 경우
		return (errmsg_cmd(cmd->command, NULL, strerror(errno),
				CMD_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}
