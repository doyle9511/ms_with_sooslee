/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:17:49 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/23 05:42:29 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_var_compliant(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (false);
	else
		return (true);
}

int	var_length(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] != '$')//$ 찾기
		i++;
	i++;//$ 다음 index
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')//$ 다음이 숫자 혹은 ?라면
		return (1);//1 반환
	while (str[i])
	{
		if (is_var_compliant(str[i]) == false)//알파벳, 숫자, '_' 전부 아니면
			break ;//이때까지의 count 반환
		count++;
		i++;
	}
	return (count);
}

char	*identify_var(char *token_str)
{
	char	*var;
	char	*tmp;
	int		start_i;
	int		len;
	int		i;

	i = 0;
	start_i = 0;
	while (token_str[i])
	{
		if (token_str[i] == '$')//환경변수 시작 찾아서 시작 index 지정(start_i)
		{
			start_i = i + 1;
			break ;
		}
		i++;
	}
	len = var_length(token_str);//$뒤의 환경변수 길이 구하기
	var = ft_substr(token_str, start_i, len);//var 문자열 구하기
	if (!var)
		return (NULL);
	tmp = ft_strjoin(var, "=");//var에 = 붙이기
	free_ptr(var);
	var = tmp;
	return (var);
}
