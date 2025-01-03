/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:02:17 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/03 10:31:42 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* realloc_env_vars:
g_env_vars 메모리 재할당
새로운 환경변수 포인터 반환, 메모리 할당 에러시 NULL 반환.
*/
static char	**realloc_env_vars(t_data *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (data->env[i] != NULL && i < size)
	{
		new_env[i] = ft_strdup(data->env[i]);
		free_ptr(data->env[i]);
		i++;
	}
	free(data->env);
	return (new_env);
}

/* set_env_var:
주어진 키에 해당하는 환경변수를 주어진 값으로 설정.
키가 이미 존재하면 값을 덮어쓰고, 없으면 새 항목 생성.
*/
bool	create_new_env(char **new_var, const char *value, const char *key)
{
	char	*tmp;

	if (value == NULL)
	{
		*new_var = ft_strdup(key);
		if (!*new_var)
			return (false);
	}
	else
	{
		tmp = ft_strjoin("=", value);
		if (!tmp)
			return (false);
		*new_var = ft_strjoin(key, tmp);
		free_ptr(tmp);
		if (!*new_var)
			return (false);
	}
	return (true);
}

bool	set_env_var(t_data *data, char *key, char *value)
{
	int		idx;
	char	*new_var;

	idx = get_env_var_index(data->env, key);
	if (idx != -1 && value == NULL)
		return (true);
	if (!create_new_env(&new_var, value, key))
		return (false);
	if (idx != -1 && data->env[idx])
	{
		free_ptr(data->env[idx]);
		data->env[idx] = new_var;
	}
	else
	{
		idx = env_var_count(data->env);
		data->env = realloc_env_vars(data, idx + 1);
		if (!data->env)
		{
			free_ptr(new_var);
			return (false);
		}
		data->env[idx] = new_var;
	}
	return (true);
}

bool	remove_env_var(t_data *data, int idx)
{
	int	i;
	int	count;

	if (idx > env_var_count(data->env))
		return (false);
	free_ptr(data->env[idx]);
	i = idx;
	count = idx;
	while (data->env[i + 1] != NULL)
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free_ptr(data->env[i + 1]);
		count++;
		i++;
	}
	data->env = realloc_env_vars(data, count);
	if (data->env == NULL)
		return (false);
	return (true);
}
