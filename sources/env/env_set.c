/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:02:17 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/23 05:38:04 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* realloc_env_vars:
*	g_env_vars 메모리 재할당
*
*	Returns a pointer to the new environment variables
*	or NULL in case of a memory allocation error.
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
*	Adds an environment variable with the given key
*	corresponding to the given value. If the key already
*	exists in the environment variables, the value will
*	be overwritten. If not, it creates a new entry.
*
*	Returns 1 if the operation was successful, or 0 if
*	in case of error.
*/
bool	set_env_var(t_data *data, char *key, char *value)
{
	int		idx;
	char	*tmp;

	idx = get_env_var_index(data->env, key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (false);
	if (idx != -1 && data->env[idx])
	{
		free_ptr(data->env[idx]);
		data->env[idx] = ft_strjoin(key, tmp);
	}
	else
	{
		idx = env_var_count(data->env);
		data->env = realloc_env_vars(data, idx + 1);
		if (!data->env)
			return (false);
		data->env[idx] = ft_strjoin(key, tmp);
	}
	free_ptr(tmp);
	return (true);
}

bool	remove_env_var(t_data *data, int idx)// 환경변수에서 지정된 인덱스의 변수 제거
{
	int	i;
	int	count;

	if (idx > env_var_count(data->env))//변수갯수보다 인덱스가 크면 false
		return (false);
	free_ptr(data->env[idx]);//지정 변수 삭제
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
