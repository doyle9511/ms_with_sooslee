/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 08:01:26 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/03 10:02:31 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	init_env(t_data *data, char **env)
{
	int	i;

	data->env = ft_calloc(env_var_count(env) + 1, sizeof * data->env);
	if (data->env == 0)
		return (false);
	i = 0;
	while (env[i] != 0)
	{
		data->env[i] = ft_strdup(env[i]);
		if (data->env[i] == 0)
			return (false);
		i++;
	}
	return (true);
}

/* init_words:
- cd 내장명령어를 위한 작업디렉토리 변수 초기화
- 환경변수 PWD 및 OLDPWD가 설정되지 않았거나 없는 경우 대비 
*/
static bool	init_words(t_data *data)
{
	char	buff[PATH_MAX];
	char	*now_dir;

	now_dir = getcwd(buff, PATH_MAX);
	data->working_dir = ft_strdup(now_dir);
	if (data->working_dir == 0)
		return (false);
	if (get_env_var_index(data->env, "OLDPWD") != -1)
	{
		data->old_working_dir = ft_strdup(get_env_var_val(data->env, "OLDPWD"));
		if (data->old_working_dir == 0)
			return (false);
	}
	else
	{
		data->old_working_dir = ft_strdup(now_dir);
		if (data->old_working_dir == 0)
			return (false);
	}
	return (true);
}

/* init_data:
data 구조체 초기화
*/
bool	init_data(t_data *data, char **env)
{
	if (init_env(data, env) == 0)
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize environment", 1);
		return (false);
	}
	if (init_words(data) == 0)
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize working directories",
			1);
		return (false);
	}
	data->token = NULL;
	data->user_input = NULL;
	data->cmd = NULL;
	data->pid = -1;
	g_last_exit_code = 0;
	return (true);
}

void	init_io(t_command *cmd)
{
	if (!cmd->io_fds)
	{
		cmd->io_fds = malloc(sizeof * cmd->io_fds);
		if (!cmd->io_fds)
			return ;
		cmd->io_fds->infile = NULL;
		cmd->io_fds->outfile = NULL;
		cmd->io_fds->heredoc_delimiter = NULL;
		cmd->io_fds->heredoc_quotes = false;
		cmd->io_fds->fd_in = -1;
		cmd->io_fds->fd_out = -1;
		cmd->io_fds->stdin_backup = -1;
		cmd->io_fds->stdout_backup = -1;
	}
}
