/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooslee <sooslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:34:59 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/31 14:53:41 by sooslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* get_key_value_pair:
주어진 인자를 환경변수용 키-값 쌍으로 분리함.
새로운 환경변수의 키와 값을 담은 2개의 문자열 배열 반환.
*/
static char	**get_key_value_pair(char *arg)
{
	char	**tmp;
	char	*eq_pos;

	if (ft_strchr(arg, '=') == NULL)
	{
		tmp = malloc(sizeof * tmp * (2 + 1));
		tmp[0] = ft_substr(arg, 0, ft_strlen(arg));
		tmp[1] = NULL;
		return (tmp);
	}
	else
	{
		eq_pos = ft_strchr(arg, '=');
		tmp = malloc(sizeof * tmp * (2 + 1));
		tmp[0] = ft_substr(arg, 0, eq_pos - arg);	
		tmp[1] = ft_substr(eq_pos, 1, ft_strlen(eq_pos));
		tmp[2] = NULL;
		return (tmp);
	}

}
void	sort_env(char **temp_env, char **temp_one)
{
	int i;
	int j;
	int size;
	
	size = 0;
	i = 0;
	while (temp_env[size] != NULL)
        size++;

	while(i < size - 1)
	{
		j = 0;
		while(j < size -1 -i)
		{
			if (ft_strcmp(temp_env[j], temp_env[j + 1]) > 0)
			{
				*temp_one = temp_env[j];
				temp_env[j] = temp_env[j + 1];
				temp_env[j + 1] = *temp_one;
			}
			j ++;
		}
		i ++;
	}
}

void	export_print(t_data *data)
{
	char **temp_env;
	char **temp;
	char *temp_one;
	int i;

	temp_env = data->env;
	sort_env(temp_env, &temp_one);
	i = 0;
	while(temp_env[i])
	{
		temp = get_key_value_pair(temp_env[i]);
		if(temp[0] && temp[1] == NULL)
		{
			printf("declare -x %s\n", temp[0]);
		}
		else if (temp[0] && temp[1])
		{
			printf("declare -x %s=\"%s\"\n", temp[0], temp[1]);
		}
		double_free(temp);
		i ++;
	}
}
/* export_builtin:
주어진 변수들을 환경변수에 추가.
모든 인자가 성공적으로 추가되면 0 반환,
*/
void	add_new_env(t_data *data, char **tmp, char **args, int *i)
{
	tmp = get_key_value_pair(args[*i]);
	if (ft_strchr(args[*i], '='))
		set_env_var(data, tmp[0], tmp[1]);
	else
		set_env_var(data, tmp[0], NULL);  // value를 NULL로 전달
	free_str_tab(tmp);
}

int export_builtin(t_data *data, char **args)
{
	int	i;
	char	**tmp;
	int	ret;
	
	ret = EXIT_SUCCESS;
	i = 1;
	tmp = NULL;
	if (!args[i])
		export_print(data);
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
		{
			errmsg_cmd("export", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else if (args[i])
		{
			add_new_env(data, tmp, args, &i);
		}
		i++;
	}
	return (ret);
}
