/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:11:41 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/03 09:54:41 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	INPUT -> REDIR_IN (<)
입력 리다이렉션 (<)
입력의 리다이렉션은 word의 확장으로 생성된 파일명을 n(fd)으로 읽기 위해 열게 됨.
n이 지정되지 않은 경우 표준 입력(0)을 사용.

입력 리다이렉션의 일반적인 형식: [n]<word
*/

/*remove_old_file_ref:
기능
1. 이전파일 참조 정리
2. 메모리 해제
3. 파일디스크립터 닫기
4. 히어독 임시파일 삭제
*/
bool	remove_old_file_ref(t_io_fds *io, bool infile)
{
	if (infile == true && io->infile)
	{
		if (io->fd_in == -1 || (io->outfile && io->fd_out == -1))
			return (false);
		if (io->heredoc_delimiter != NULL)
		{
			free_ptr(io->heredoc_delimiter);
			io->heredoc_delimiter = NULL;
			unlink(io->infile);
		}
		free_ptr(io->infile);
		close(io->fd_in);
	}
	else if (infile == false && io->outfile)
	{
		if (io->fd_out == -1 || (io->infile && io->fd_in == -1))
			return (false);
		free_ptr(io->outfile);
		close(io->fd_out);
	}
	return (true);
}

/* open_infile:
입력 파일을 여는 함수. 
이미 입력 파일이 설정되어 있다면 -> 해제 + 덮어쓰기
이전 입력 파일 열기 실패(파일이 존재 X || 권한 X) -> 더 이상의 입력 파일을 열지 않기

ex)
1. < Makefile <README.md cat > test
	→ README.md의 내용을 입력으로 사용 (Makefile은 무시)
2. < forbidden <README.md cat > test
	→ 권한 거부 (README도 처리되지 않음)
*/
static void	open_infile(t_io_fds *io, char *file, char *origin_file)
{
	if (!remove_old_file_ref(io, true))
		return ;
	io->infile = ft_strdup(file);
	if (io->infile && io->infile[0] == '\0')
	{
		errmsg_cmd(origin_file, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
		errmsg_cmd(io->infile, NULL, strerror(errno), false);
}

void	parse_input(t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	open_infile(cmd->io_fds, temp->next->str, temp->next->str_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
