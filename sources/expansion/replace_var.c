/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:12:11 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/23 05:43:58 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	erase_var(t_token **token_node, char *str, int index)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = ft_strlen(str) - var_length(str + index);
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (1);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			i = i + var_length(str + index) + 1;
			if (str[i] == '\0')
				break ;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free_ptr((*token_node)->str);
	(*token_node)->str = new_str;
	return (0);
}

/*
1. 반환 타입 변경:
int에서 char *로 변경됨
히어독의 변수 확장을 위해 수정됨
2. 파라미터 변경 이유:
히어독은 토큰을 사용하지 않음
따라서 token_node 매개변수가 선택적(optional)이 됨
3. 사용 예시:
replace_str_heredoc 함수가 이 함수를 호출할 때
token_node를 NULL로 전달함
*/
static char	*erase_and_replace(t_token **token_node, char *str,
			char *var_value, int index)
{
	char	*newstr;
	int		newstr_size;

	newstr_size = (ft_strlen(str) - var_length(str + index)
			+ ft_strlen(var_value));
	newstr = get_new_token_string(str, var_value, newstr_size, index);
	if (token_node && *token_node)
	{
		free_ptr((*token_node)->str);
		(*token_node)->str = newstr;
	}
	return (newstr);
}

int	replace_var(t_token **token_node, char *var_value, int index)
{
	if (var_value == NULL)//value값이 안들어왔을땐, var 지우기
	{
		if (erase_var(token_node, (*token_node)->str, index) == 1)
		{
			free_ptr(var_value);
			return (1);
		}
	}
	else
	{
		if (erase_and_replace(token_node, (*token_node)->str, \
		var_value, index) == NULL)
		{
			free_ptr(var_value);
			return (1);
		}
	}
	free_ptr(var_value);
	return (0);
}

/* replace_str_heredoc:
*	Heredoc variant of replace_var, replaces an environment variable
*	by its value. Ex. $USER -> username.
*	Returns the replaced string.
*/

char	*replace_str_heredoc(char *str, char *var_value, int index)
{
	char	*tmp;

	tmp = NULL;
	if (var_value == NULL)
		*str = '\0';
	else
	{
		tmp = str;
		str = erase_and_replace(NULL, str, var_value, index);
		free_ptr(tmp);
	}
	free_ptr(var_value);
	return (str);
}
