/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:09:12 by mcombeau          #+#    #+#             */
/*   Updated: 2024/12/13 00:25:05 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	init_env(t_data *data, char **env)//원본 쉘로부터 상속받은 환경변수 내용으로 데이터 변수 초기화
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
	char	*now_dir;//현재 디렉토리 저장할 문자열

	now_dir = getcwd(buff, PATH_MAX);//현재위치 획득
	data->working_dir = ft_strdup(now_dir);//data에 현재위치 저장
	if (data->working_dir == 0)
		return (false);
	if (get_env_var_index(data->env, "OLDPWD") != -1)//OLDPWD인 환경변수 획득시
	{
		data->old_working_dir = ft_strdup(get_env_var_val(data->env, "OLDPWD"));//data에 이전위치 저장
		if (data->old_working_dir == 0)
			return (false);
	}
	else//못찾으면(== 터미널 처음 실행시) ; PWD와 같음
	{
		data->old_working_dir = ft_strdup(now_dir);//이전구조체에 현재 위치저장
		if (data->old_working_dir == 0)
			return (false);
	}
	return (true);
}

/* init_data:
*	Initializes the data structure used in parsing and executing user input.
*	Returns true if successful, false in case of error.
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

/* init_io:
*	Initializes a structure with default values to contain
*	infile and outfile information for a command.
*/
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
