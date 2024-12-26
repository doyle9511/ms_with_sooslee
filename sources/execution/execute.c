/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:11:43 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/26 17:09:19 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_code;

/* get_children:
파일 디스크립터와 명령어 리스트를 정리한 후 자식 프로세스들의 종료 대기

1. 단일 명령어의 경우:
	- POSIX waitpid 함수가 제공하는 종료 상태를 반환
	- 시그널로 종료된 경우 128+n 반환 (n:시그널 번호)
2. 파이프라인의 경우:
	- 파이프라인의 마지막 명령어의 종료 상태를 반환
*/
static int	get_children(t_data *data)
{
	pid_t	pidt;
	int		status;
	int		save_stat;

	close_fds(data->cmd, false);
	save_stat = 0;
	pidt = 0;
	while (pidt != -1 || errno != ECHILD)//자식이 남아있는 동안
	{
		pidt = waitpid(-1, &stat, 0);//아무 자식이나 대기
		if (pidt == data->pid)//마지막 명령어라면
			save_stat = stat;//상태 저장
		continue ;
	}
	if (WIFSIGNALED(save_stat))//시그널로 종료된 경우(ctrl + C)
		stat = 128 + WTERMSIG(save_stat);
	else if (WIFEXITED(save_stat))//정상종료된 경우
		stat = WEXITSTAT(save_stat);
	else//기타
		stat = save_stat;
	return (stat);
}

/* create_children:
각 명령어를 실행하기 위한 자식 프로세스를 생성
단, 파이프 없는 빌트인 명령어의 경우는 예외로 메인프로세스에서 실행 (자식 프로세스 생성x)
*/
static int	create_children(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	while (data->pid != 0 && cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (errmsg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (data->pid == 0)
			execute_command(data, cmd);
		cmd = cmd->next;
	}
	return (get_children(data));
}

/* prep_for_exec:
prep_for_exec:
명령어 리스트를 실행하기 위해 준비하는 과정
- 파이프를 생성
- 입력/출력 파일들을 확인
실행 준비가 완료 -> true
*/
static int	prep_for_exec(t_data *data)
{
	if (!data || !data->cmd)//기본 유효성 검사
		return (EXIT_SUCCESS);
	if (!data->cmd->command)//명령어 없는 경우(= 리다이렉션만 있는 경우)
	{
		if (data->cmd->io_fds && !check_infile_outfile(data->cmd->io_fds))
			return (EXIT_FAILURE);//입출력파일 확인
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))//파이프 생성
		return (EXIT_FAILURE);
	return (CMD_NOT_FOUND);
}

/* execute:
- 주요 기능:
	주어진 명령어들을 실행
	자식 프로세스들을 생성
	자식 프로세스들의 종료를 기다림
- 반환값:
	정상 실행: 마지막으로 종료된 자식 프로세스의 종료 코드
	오류 발생: 자식 프로세스 생성 실패시 1을 반환
- 동작 방식:
	fork()를 통한 자식 프로세스 생성
	부모 프로세스는 wait/waitpid로 자식들의 종료를 기다림
*/
int	execute(t_data *data)
{
	int	ret;

	ret = prep_for_exec(data);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	if (!data->cmd->pipe_output && !data->cmd->prev
		&& check_infile_outfile(data->cmd->io_fds))
	{
		redirect_io(data->cmd->io_fds);
		ret = execute_builtin(data, data->cmd);
		restore_io(data->cmd->io_fds);
	}
	if (ret != CMD_NOT_FOUND)
		return (ret);
	return (create_children(data));
}
