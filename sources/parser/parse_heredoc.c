/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:19:23 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/26 17:36:33 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* get_heredoc:
사용자 입력을 기다리는 히어독 오픈.
주어진 변수들을 환경변수 값으로 변환합니다.
*/
bool	get_heredoc(t_data *data, t_io_fds *io)
{
	int		tmp_fd;
	bool	ret;

	ret = true;
	tmp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ret = fill_heredoc(data, io, tmp_fd);
	close(tmp_fd);
	return (ret);
}

/* get_heredoc_name:
현재 히어독을 위한 고유 이름 생성.
새로운 히어독 이름 반환.
*/
static char	*get_heredoc_name(void)
{
	static int	i;
	char		*hd_name;
	char		*hd_num;

	hd_num = ft_itoa(i);
	if (!hd_num)
		return (NULL);
	hd_name = ft_strjoin(HEREDOC_NAME, hd_num);
	free(hd_num);
	i++;
	return (hd_name);
}

/* get_delim:
히어독 구분자를 반환.
구분자 주위에 따옴표가 있으면 제거하고 quotes 불리언을 true로 설정.
//예시:
//	<< EOF      # quotes = false
//	<< 'EOF'    # quotes = true
//	<< "EOF"    # quotes = true
*/
static char	*get_delim(char *delim, bool *quotes)
{
	int	len;

	len = ft_strlen(delim) - 1;
	if ((delim[0] == '\"' && delim[len] == '\"')
		|| (delim[0] == '\'' && delim[len] == '\''))
	{
		*quotes = true;
		return (ft_strtrim(delim, "\'\""));
	}
	return (ft_strdup(delim));
}

/* parse_heredoc:
사용자 입력으로 채워질 임시 히어독 파일 생성.

//히어독 예시:
//	cat << EOF
//	hello $USER
//	world
//	EOF
//	진행과정	
//		1. 임시파일 생성 (minishell_heredoc_0)
//		2. '>'프롬프트로 입력받기
//		3. 
*/
void	parse_heredoc(t_data *data, t_command **last_cmd, t_token **token_lst)
{
	t_token		*tmp;
	t_command	*cmd;
	t_io_fds	*io;

	tmp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	io = cmd->io_fds;
	if (!remove_old_file_ref(io, true))
		return ;
	io->infile = get_heredoc_name();
	io->heredoc_delimiter = get_delim(tmp->next->str, &(io->heredoc_quotes));
	if (get_heredoc(data, io))
		io->fd_in = open(io->infile, O_RDONLY);
	else
		io->fd_in = -1;
	if (tmp->next->next)
		tmp = tmp->next->next;
	else
		tmp = tmp->next;
	*token_lst = tmp;
}
