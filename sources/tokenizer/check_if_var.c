/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:40:24 by alexa             #+#    #+#             */
/*   Updated: 2024/12/19 14:58:49 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	consecutive_ops(t_token *token_node)//seperator 연속사용(+ END) 체크
{
	if (token_node->prev != 0)
	{
		if (token_node->type == PIPE && token_node->prev->type == PIPE)// = '||'
			return (false);
		if (token_node->type > PIPE && token_node->prev->type > PIPE)// = '<< <<' '< >' '> >'등등
			return (false);
		if (token_node->type == END && token_node->prev->type >= PIPE)// '| \0'
			return (false);
	}
	return (true);
}

int	check_consecutives(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	while (temp)
	{
		if (consecutive_ops(temp) == false)//sep연속사용했을 때 출력될 에러메세지 선택
		{
			if (temp->type == END && temp->prev && temp->prev->type > PIPE)
				errmsg("syntax error near unexpected token", "newline", true);
			else if (temp->type == END && temp->prev)
				errmsg("syntax error near unexpected token",
					temp->prev->str, true);
			else
				errmsg("syntax error near unexpected token", temp->str, true);
			return (FAILURE);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

static void	variable_check(t_token **token_node)
{
	int	i;

	i = 0;
	while ((*token_node)->str[i])//'$' 즉, [환경변수] 발견할 때 까지 순환
	{
		if ((*token_node)->str[i] == '$')
		{
			if ((*token_node)->prev && (*token_node)->prev->type == HEREDOC)
				break ;//이전 노드가 [히어독]이면 타입지정 스킵
			(*token_node)->type = VAR;//$ 발견시 VAR 지정
			return ;
		}
		i++;
	}
}

int	check_if_var(t_token **token_lst)
{
	t_token	*temp;

	temp = *token_lst;
	if (temp->type == PIPE)//토큰 최상단이 파이프면, 즉 파이프가 제일 처음이면
	{
		errmsg("syntax error near unexpected token", temp->str, true);
		return (FAILURE);
	}
	while (temp)//토큰이 끝날 때 까지
	{
		variable_check(&temp);//
		if (check_consecutives(&temp) == FAILURE)
			return (FAILURE);
		temp = temp->next;
	}
	return (SUCCESS);
}
