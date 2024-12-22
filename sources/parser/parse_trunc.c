/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_trunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:19:21 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/23 05:55:19 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
TRUNC -> 출력 리다이렉션
word의 확장으로 생성된 파일명을 가진 파일은
파일 디스크립터 n으로 쓰기 모드로 열려야 함.
n이 지정되지 않은 경우 표준 출력(fd 1) 사용.

파일이 존재하지 않으면: 새로 생성
파일이 이미 존재하면: 크기를 0으로 truncate(내용 비우기)

출력 리다이렉션의 일반적인 형식: [n]>[|]word
*/

// char	*get_relative_path(char *file_to_open)//파일경로를 절대경로
// {
// 	char	*path;
// 	char	*ret;

// 	if (file_to_open[0] == '/')
// 		return (ft_strdup(file_to_open));
// 	path = ft_strdup("./");
// 	ret = ft_strjoin(path, file_to_open);
// 	printf("PARSING - Get_rel_path function return : %s\n", ret);
// 	return (ret);
// }

/* open_outfile_trunc:
출력 파일을 truncate 모드로 열기(깨끗히 비우고 새로 시작하는 모드)
이미 출력 파일이 설정되어 있다면, 해제 + 덮어쓰기
이전 입,출력 파일 열기 실패시 (파일 존재x || 권한x) -> 더 이상 출력파일 열기 x
ex)
1. echo hello > forbidden_file > test
2. echo hello >> forbidden_file > test
3. < forbidden_file cat > test
이 세 경우 모두 test 파일은 열리거나 생성되지 않아야 함
*/
static void	open_outfile_trunc(t_io_fds *io, char *file, char *var_filename)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0')
	{
		errmsg_cmd(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd_out == -1)
		errmsg_cmd(io->outfile, NULL, strerror(errno), false);
}

void	parse_trunc(t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	open_outfile_trunc(cmd->io_fds, temp->next->str, temp->next->str_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
