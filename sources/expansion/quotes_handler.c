/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:39:40 by alexa             #+#    #+#             */
/*   Updated: 2024/12/22 21:47:09 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len(char *str, int count, int i)
{
	int	status;

	status = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && status == DEFAULT)
		{
			if (str[i] == '\'')
				status = SQUOTE;
			if (str[i] == '\"')
				status = DQUOTE;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && status == SQUOTE)
			|| (str[i] == '\"' && status == DQUOTE))
		{
			status = DEFAULT;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

bool	quotes_in_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

int	handle_quotes(t_data *data)//쉘에서 따옴표는 단어구분 무시하고 인자처리, 실제 명령시에는 따옴표 필요없음 / HEREDOC은 구분자로 따옴표 가능
{
	t_token	*temp;

	temp = data->token;
	while (temp)
	{
		if (quotes_in_string(temp->str) == true// 따옴표가 존재하고, 
			&& (!temp->prev || (temp->prev && temp->prev->type != HEREDOC)))// 첫 토큰이거나(segfalt 방지), 이전토큰이 HEREDOC이 아니면
			remove_quotes(&temp);//따옴표 제거
		temp = temp->next;
	}
	return (0);
}
