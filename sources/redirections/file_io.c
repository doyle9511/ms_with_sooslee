/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:11:30 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/23 06:21:56 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* restore_io:
원래의 표준 입력과 표준 출력을 원래의 파일 디스크립터 0과 1로 복원
실행 후 입/출력 fd를 정리하고 다음 사용자 명령을 준비하는데 사용
복제가 성공하면 1, 실패하면 0을 반환
*/
bool	restore_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	if (io->stdin_backup != -1)
	{
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			ret = false;
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1)
	{
		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
			ret = false;
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	return (ret);
}

/* redirect_io:
입력과 출력 fd를 표준 입력과 출력으로 복제
실행 후 복원하기 위해 표준 입력과 출력을 교체하기 전에 백업
성공시 1, 오류시 0을 반환
*/
bool	redirect_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
		ret = errmsg_cmd("dup", "stdin backup", strerror(errno), false);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		ret = errmsg_cmd("dup", "stdout backup", strerror(errno), false);
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			ret = errmsg_cmd("dup2", io->infile, strerror(errno), false);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			ret = errmsg_cmd("dup2", io->outfile, strerror(errno), false);
	return (ret);
}

bool	check_infile_outfile(t_io_fds *io)//infile + outfile 있는지 확인
{
	if (!io || (!io->infile && !io->outfile))//io가 NULL이거나 입/출력 파일 둘다 없음
		return (true);//리다이렉션 없으면 OK
	if ((io->infile && io->fd_in == -1)//입력파일 있는데 fd가 -1 : 파일열기 실패 
		|| (io->outfile && io->fd_out == -1))//출력파일 있는데 fd가 -1 : 파일열기 실패
		return (false);//리다이렉션 실패 FAIL
	return (true);//모든 리다이렉션 성공 OK
}
