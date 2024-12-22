/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 02:35:14 by alexa             #+#    #+#             */
/*   Updated: 2024/12/22 21:25:47 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*  After splitting the user's input into tokens, we have to expand 
*  the variables. After the expansion is done, quote characters are
*  removed from the original word unless they are between quotes.
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

static bool	is_next_char_a_sep(char c)//다음 index가 $, ' ', =, \0 인가? -> true
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
		if (tmp->type == VAR)//토큰노드 타입이 환경변수면?
		{
			i = 0;
			while (tmp->str[i])
			{
				update_status(&tmp, tmp->str[i]);//''인지 ""인지 구별->status 저장
				if (tmp->str[i] == '$'// i가 $이고
					&& is_next_char_a_sep(tmp->str[i + 1]) == false// $ 다음이 [$, ' ', =, \0]가 아니고,
					&& var_between_quotes(tmp->str, i) == false// $ 앞뒤로 " 가 없으며, ( "$" ) 
					&& (tmp->status == DEFAULT || tmp->status == DQUOTE))//따옴표 밖에 있거나 "" 안에 있을 때 -> 즉, [정상적인 "$VAR" 일때]
					replace_var(&tmp, recover_val(tmp, tmp->str + i, data), i);// token_str에서 $*** 없애기 (recover_val : key($***=)와 대응되는 value값 리턴됨)
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
		if (tkn[i] == '$' && is_next_char_a_sep(tkn[i + 1]) == false\
			&& var_between_quotes(tkn, i) == false)
			tkn = replace_str_heredoc(tkn, recover_val(NULL, tkn + i, data), i);
		else
			i++;
	}
	return (tkn);
}
