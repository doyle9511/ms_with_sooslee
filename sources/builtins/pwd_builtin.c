/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:51:26 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/26 16:08:02 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* pwd_builtin:
pwd 내장 명령어를 실행하고 현재 작업 디렉토리 경로를 표시.
*/
int	pwd_builtin(t_data *data, char **argus)
{
	char	buff[PATH_MAX];
	char	*cwd_str;

	(void)argus;
	if (data->working_dir)
	{
		ft_putendl_fd(data->working_dir, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	cwd_str = getcwd(buff, PATH_MAX);
	if (cwd_str)
	{
		ft_putendl_fd(cwd_str, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	errmsg_cmd("pwd", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
