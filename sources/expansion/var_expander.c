/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:01:51 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/03 13:13:53 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
사용자의 입력을 토큰으로 분할한 후, 변수들을 확장해야 함(expand).
변수 확장이 완료되면, 따옴표 안에 있지 않은 따옴표 문자들은 원래 단어에서 제거.
*/

static void	update_status(t_token **token_node, char c)
{
	if (c == '\'' && (*token_node)->status == DEFAULT)
		(*token_node)->status = SQUOTE;
	else if (c == '\"' && (*token_node)->status == DEFAULT)
		(*token_node)->status = DQUOTE;
	else if (c == '\'' && (*token_node)->status == SQUOTE)
		(*token_node)->status = DEFAULT;
	else if (c == '\"' && (*token_node)->status == DQUOTE)
		(*token_node)->status = DEFAULT;
}

static bool	is_next_char_a_sep(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	else
		return (false);
}

static bool	var_between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (true);
		else
			return (false);
	}
	return (false);
}

int	var_expander(t_data *data, t_token **token_lst)
{
	t_token	*tmp;
	int		i;

	tmp = *token_lst;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			i = 0;
			while (tmp->str[i])
			{
				update_status(&tmp, tmp->str[i]);
				if (tmp->str[i] == '$'
					&& is_next_char_a_sep(tmp->str[i + 1]) == false
					&& var_between_quotes(tmp->str, i) == false
					&& (tmp->status == DEFAULT || tmp->status == DQUOTE))
					replace_var(&tmp, recover_val(tmp, tmp->str + i, data), i);
				else
					i++;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

/* 이는 히어독(heredoc) 문맥에서 환경변수를 처리하는 함수에 대한 주석입니다.
주요 기능:

- $USER와 같은 환경변수가 포함된 문자열을 발견하면
- 해당 환경변수의 실제 값으로 대체
- 오류 발생시 NULL을 반환할 수 있음
일반적인 var_expander의 히어독 버전이라고 보면 됩니다.
*/
char	*var_expander_heredoc(t_data *data, char *tkn)
{
	int	i;

	i = 0;
	while (tkn[i])
	{
		if (tkn[i] == '$' && is_next_char_a_sep(tkn[i + 1]) == false
			&& var_between_quotes(tkn, i) == false)
			tkn = replace_str_heredoc(tkn, recover_val(NULL, tkn + i, data), i);
		else
			i++;
	}
	return (tkn);
}
