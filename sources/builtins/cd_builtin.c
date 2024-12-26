/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:13:29 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/26 15:06:03 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* update_wds:
디렉토리 변경 후 환경변수의 PWD와 OLDPWD를 업데이트함.
환경변수가 설정되지 않은 경우를 대비해 내부적으로 경로 복사본을 같이 업데이트
*/
static void	update_wds(t_data *data, char *path_str)
{
	set_env_var(data, "OLDPWD", get_env_var_val(data->env, "PWD"));
	set_env_var(data, "PWD", path_str);
	if (data->old_working_dir)
	{
		free_ptr(data->old_working_dir);
		data->old_working_dir = ft_strdup(data->working_dir);
	}
	if (data->working_dir)
	{
		free_ptr(data->working_dir);
		data->working_dir = ft_strdup(path_str);
	}
	free_ptr(path_str);
}

/* chdir_errno_mod:
일부 시스템에서 상위 디렉토리가 제거될 때 chdir이 ESTALE("Stale file handle") 
errno를 설정할 수 있음. 이는 inode 테이블 항목이 재사용되어서 발생.
"no such file or directory" 에러를 대신 표시하기 위한 수정.
*/
static	bool	chdir_errno_mod(char *path_str)
{
	if (errno == ESTALE)//errno : 시스템 에러 번호를 저장하는 변수
		errno = ENOENT;//ESTALE(116) : 이동 및 삭제된 디렉토리로 접근하려할 때 발생하는 에러 / ENOENT(2) : "No such file or directory" 에러번호
	errmsg_cmd("cd", path_str, strerror(errno), errno);//e
	return (false);
}

/* change_dir:
현재 작업 디렉토리를 변경하고 OLDPWD 환경변수를 업데이트함.
*/
static bool	change_dir(t_data *data, char *path)
{
	char	*path_str;
	char	*tmp;
	char	cwd[PATH_MAX];

	path_str = NULL;
	if (chdir(path) != 0)
		return (chdir_errno_mod(path));
	path_str = getcwd(cwd, PATH_MAX);
	if (!path_str)
	{
		errmsg_cmd("cd: error retrieving current directory",
			"getcwd: cannot access parent directories",
			strerror(errno), errno);
		path_str = ft_strjoin(data->working_dir, "/");
		tmp = path_str;
		path_str = ft_strjoin(tmp, path);
		free_ptr(tmp);
	}
	else
		path_str = ft_strdup(cwd);
	update_wds(data, path_str);
	return (true);
}

/* cd_builtin:
내장 cd 명령어를 실행하여 작업 디렉토리를 변경함.
*/
int	cd_builtin(t_data *data, char **args)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0])
		|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
	{
		path = get_env_var_val(data->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	if (args[2])
		return (errmsg_cmd("cd", NULL, "too many arguments", EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_var_val(data->env, "OLDPWD");
		if (!path)
			return (errmsg_cmd("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	return (!change_dir(data, args[1]));
}
