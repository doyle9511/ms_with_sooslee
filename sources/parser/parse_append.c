/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:42:44 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/26 17:49:35 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
APPEND 리다이렉션:
출력을 추가 모드로 리다이렉션하면 word의 확장으로 얻은 이름의 파일이 파일 디스크립터 n에 대해 추가 모드로 오픈.
n이 지정되지 않으면 표준 출력(fd 1)이 사용됩니다.
파일이 없으면 생성됩니다.

일반적인 형식: [n]>>word
*/

/* open_outfile_append:
주석: 추가 모드로 출력 파일을 엽니다. 출력 파일이 이미 설정되어 있으면 해제하고 덮어씀.
이전 입력/출력 파일 열기가 실패한 경우 (파일이 없거나 권한이 거부됨) 추가 출력 파일을 열지 않음.

//	예시:
//	echo hello > forbidden_file >> test
//	echo hello >> forbidden_file >> test
//	< forbidden_file cat >> test
//	이 세 경우 모두 test 파일은 열리거나 생성되지 않아야 함
*/
static void	open_outfile_append(t_io_fds *io, char *file, char *var_filename)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0' && var_filename)
	{
		errmsg_cmd(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (io->fd_out == -1)
		errmsg_cmd(io->outfile, NULL, strerror(errno), false);
}

//echo "hello" >> file.txt  # file.txt에 추가
//ls >> log.txt            # log.txt에 추가
void	parse_append(t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	open_outfile_append(cmd->io_fds, temp->next->str, temp->next->str_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
