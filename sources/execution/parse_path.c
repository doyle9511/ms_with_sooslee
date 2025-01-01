/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:46:18 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/01 21:57:30 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* find_valid_cmd_path:
명령어의 바이너리 파일에 대한 유효한 경로를 찾기 위해 각 가능한 명령어 경로의 접근권한과 허가 확인.
유효한 명령어 바이너리 경로를 반환하거나, 유효한 경로가 없으면 NULL 반환.
*/
static char	*find_valid_cmd_path(char *command, char **paths)
{
	int		i;
	char	*command_path;

	command_path = NULL;
	i = 0;
	while (paths[i])
	{
		command_path = ft_strjoin(paths[i], command);
		if (!command_path)
		{
			errmsg_cmd("malloc", NULL,
				"an unexpected error occured", EXIT_FAILURE);
			return (NULL);
		}
		if (access(command_path, F_OK | X_OK) == 0)
			return (command_path);
		free_ptr(command_path);
		i++;
	}
	return (NULL);
}

/* get_paths_from_env:
PATH 환경변수에서 경로들을 추출 시도.
성공시 경로 배열 반환. 실패시 NULL 반환.
// PATH 환경변수 확인 후 ':' 기준으로 분리
// 예: /usr/local/bin:/usr/bin:/bin
*/
static char	**get_paths_from_env(t_data *data)
{
	char	**env_paths;

	if (get_env_var_index(data->env, "PATH") == -1)
		return (NULL);
	env_paths = ft_split(get_env_var_val(data->env, "PATH"), ':');
	if (!env_paths)
		return (NULL);
	return (env_paths);
}

/* get_cmd_path:
주어진 명령어의 바이너리 파일 위치를 PATH 환경변수에서 검색.
명령어 바이너리 파일의 경로 반환. 유효한 경로가 없으면 NULL 반환.

# 예: ls 명령어 실행시
	1. PATH=/usr/local/bin:/usr/bin:/bin  # PATH 환경변수 가져옴
	2. 각 경로에 "/ls" 추가해서 검색:
		- /usr/local/bin/ls
		- /usr/bin/ls
		- /bin/ls
	3. 실행 가능한 첫 번째 경로 반환
*/
char	*get_cmd_path(t_data *data, char *name)
{
	char	**env_paths;
	char	*command;
	char	*command_path;

	if (!name)
		return (NULL);
	env_paths = get_paths_from_env(data);//환경변수 가져오기 (PATH=/usr/local/bin:usr/bin:/bin)
	if (!env_paths)//						env_paths = ["/usr/local/bin" ... , "/bin"]
		return (NULL);
	command = ft_strjoin("/", name);//명령어 앞에 '/'추가 (name : "ls" -> command : "/ls")
	if (!command)
	{
		free_str_tab(env_paths);
		return (NULL);
	}
	command_path = find_valid_cmd_path(command, env_paths);//유효한 경로 찾기 (각 경로에 "/ls"추가해서 존재하는지 체크)
	if (!command_path)
	{
		free_ptr(command);
		free_str_tab(env_paths);
		return (NULL);
	}
	return (command_path);//일치하는 경로 반환
}
