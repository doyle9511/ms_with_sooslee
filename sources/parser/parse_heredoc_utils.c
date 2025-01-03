/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:53:12 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/26 17:29:22 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* make_str_from_tab:
문자열 배열을 하나의 문자열로 만듦.
다음 문자열과 연결하여 하나의 문자열 생성.
// 예시:
// 입력: ["hello", "world", "!"]
// 출력: "hello world !"
*/
static char	*make_str_from_tab(char **tab)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	while (tab[++i])
	{
		tmp = str;
		if (i == 0)
			str = ft_strdup(tab[0]);
		else
		{
			str = ft_strjoin(tmp, tab[i]);
			free_ptr(tmp);
		}
		if (tab[i + 1])
		{
			tmp = str;
			str = ft_strjoin(tmp, " ");
			free_ptr(tmp);
		}
	}
	free_str_tab(tab);
	return (str);
}

/* get_exoanded_var_line:
환경변수 확장을 위해 '$'가 포함된 라인을 준비.
존재하지 않는 환경변수 문제를 피하기 위해 라인을 단어로 분리.
예시: $USER uses $LANGUAGE -> username uses en_US:en
*/
static char	*get_expanded_var_line(t_data *data, char *line)
{
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			words[i] = var_expander_heredoc(data, words[i]);
			if (!words[i])
				return (NULL);
		}
		i++;
	}
	return (make_str_from_tab(words));
}

/* eval_herdoc_line:
읽은 라인을 heredoc 파일에 써야 하는지 검사.
라인이 NULL이거나 주어진 구분자와 같으면 false 반환 (readline으로 읽기 중단을 의미).
그 외의 경우 true 반환.
*/
static bool	eval_herdoc_line(t_data *data, char **line, t_io_fds *io, bool *ret)
{
	if (*line == NULL)
	{
		errmsg_cmd("warning", "here-document delimited by end-of-file: wanted",
			io->heredoc_delimiter, true);
		*ret = true;
		return (false);
	}
	if (ft_strcmp(*line, io->heredoc_delimiter) == 0)
	{
		*ret = true;
		return (false);
	}
	if (io->heredoc_quotes == false && ft_strchr(*line, '$'))
	{
		*line = get_expanded_var_line(data, *line);
		if (!(*line))
		{
			free_ptr(*line);
			*ret = false;
			return (false);
		}
	}
	return (true);
}

/* fill_heredoc:
사용자 입력을 임시 파일에 복사.
사용자가 $USER와 같은 환경변수를 입력하면 heredoc에 쓰기 전에 변수를 확장.
//예시:
//	cat << EOF
//	Hello $USER!
//	Your home is $HOME
//	EOF
*/
bool	fill_heredoc(t_data *data, t_io_fds *io, int fd)
{
	char	*line;
	bool	ret;

	ret = false;
	line = NULL;
	while (1)
	{
		set_signal();
		line = readline(">");
		if (!eval_herdoc_line(data, &line, io, &ret))
			break ;
		ft_putendl_fd(line, fd);
		free_ptr(line);
	}
	free_ptr(line);
	return (ret);
}
