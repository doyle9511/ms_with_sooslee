/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:52:13 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/26 16:10:30 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* unset_builtin:
유효성 검사 후 주어진 키에 해당하는 환경변수들을 제거.
환경변수에 없는 키는 아무 작업도 하지 않음.

$ export TEST=123    # 환경변수 설정
$ unset TEST        # 환경변수 제거
$ unset 123TEST     # 오류: 유효하지 않은 식별자
$ unset NOEXIST     # 존재하지 않는 변수 (아무 일도 일어나지 않음)
*/
int	unset_builtin(t_data *data, char **argus)
{
	int	i;
	int	j;
	int	code;

	code = EXIT_SUCCESS;
	i = 1;
	while (argus[i])
	{
		if (!is_valid_env_var_key(argus[i]) || ft_strchr(argus[i], '=') != NULL)
		{
			errmsg_cmd("unset", argus[i], "not a valid identifier", false);
			code = EXIT_FAILURE;
		}
		else
		{
			j = get_env_var_index(data->env, argus[i]);
			if (j != -1)
				remove_env_var(data, j);
		}
		i++;
	}
	return (code);
}
