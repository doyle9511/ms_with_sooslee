/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:20:13 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/31 22:18:54 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_data *data, int exit_num)//전부 닫고 해제하고 exit
{
	if (data != NULL)
	{
		if (data->cmd != NULL && data->cmd->io_fds != 0)
			close_fds(data->cmd, true);//부모프로세스에서는 계속 실행돼야 하므로 표준입출력 복원 필요함-> true->restore_io()
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
		if (parse_user_input(data) == true)//token화 시켜서 command로 전환
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
