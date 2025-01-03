/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:20:13 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/03 10:02:39 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_data *data, int exit_num)
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
	ft_memset(&data, 0, sizeof(t_data));
	if (init_data(&data, env) == false)
		exit_shell(NULL, EXIT_FAILURE);
	minishell_run(&data);
	exit_shell(&data, g_last_exit_code);
	return (0);
}
