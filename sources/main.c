/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:08:47 by mcombeau          #+#    #+#             */
/*   Updated: 2024/12/13 00:41:32 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_data *data, int exit_num)//전부 닫고 해제하고 exit
{
	if (data != NULL)
	{
		if (data->cmd != NULL && data->cmd->io_fds != 0)
			close_fds(data->cmd, true);
		free_data(data, true);
	}
	exit(exit_num);
}

void	minishell_run(t_data *data)
{
	while (1)
	{
		set_signal();
		data->user_input = readline("Minishell $>");
		if (parse_user_input(data) == true)
			g_last_exit_code = execute(data);
		else
			g_last_exit_code = 1;
		free_data(data, false);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	ft_memset(&data, 0, sizeof(t_data));//data 구조체 초기화
	if (init_data(&data, env) == false)
		exit_shell(NULL, EXIT_FAILURE);//시작조건 체크하고 초기화 실패시 종료 
	minishell_run(&data);
	exit_shell(&data, g_last_exit_code);
	return (0);
}
