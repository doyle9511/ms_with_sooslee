/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:26:14 by mcombeau          #+#    #+#             */
/*   Updated: 2024/12/22 20:57:06 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_exists(t_data *data, char *var)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var, len) == 0)
			return (0);
		i++;
	}
	return (1);
}

static char	*search_env_var(t_data *data, char *var)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var, len) == 0)
			break ;
		i++;
	}
	str = ft_strdup(data->env[i] + len);
	return (str);
}

char	*recover_val(t_token *token, char *token_str, t_data *data)
{
	char	*value;
	char	*var;

	var = identify_var(token_str);// "var_str=" 반환
	if (var && var_exists(data, var) == 0)//"var"이 존재한다면
	{
		if (token != NULL)
			token->var_exists = true;
		value = search_env_var(data, var);//value 저장
	}
	else if (var && var[0] == '?' && var[1] == '=')// "$?=" 이면
		value = ft_itoa(g_last_exit_code);//g_last_exit_code를 value값에 저장
	else
		value = NULL;
	free_ptr(var);
	return (value);
}
