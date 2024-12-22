/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:09:49 by mcombeau          #+#    #+#             */
/*   Updated: 2024/12/22 22:19:30 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_code;

/* get_children:
*	Waits for children to terminate after cleaning up fds and the command
*	list.
*	Returns a child's exit status as bash does:
*		"The return status (see Exit Status) of a simple command is its
*		exit status as provided by the POSIX 1003.1 waitpid function, or
*		128+n if the command was terminated by signal n."
*	If there are multiple commands in a pipeline:
*		"The exit status of a pipeline is the exit status of the last command
*		in the pipeline"
*/
static int	get_children(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(data->cmd, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
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
	if (!data || !data->cmd)
		return (EXIT_SUCCESS);
	if (!data->cmd->command)//명령어 없는 경우(= 리다이렉션만 있는 경우)
	{
		if (data->cmd->io_fds
			&& !check_infile_outfile(data->cmd->io_fds))//입출력파일 있으면 성공
			return (EXIT_FAILURE);
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
