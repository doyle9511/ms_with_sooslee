/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 07:11:32 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/23 06:01:50 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data, bool clear_history)//사용했던 데이터 전부 해제
{
	if (data != NULL && data->user_input != NULL)
	{
		free_ptr(data->user_input);
		data->user_input = NULL;
	}
	if (data != NULL && data->token != NULL)
		lstclear_token(&data->token, &free_ptr);
	if (data != NULL && data->cmd != NULL)
		lst_clear_cmd(&data->cmd, &free_ptr);
	if (clear_history == true)
	{
		if (data != NULL && data->working_dir != NULL)
			free_ptr(data->working_dir);
		if (data != NULL && data->old_working_dir != NULL)
			free_ptr(data->old_working_dir);
		if (data != NULL && data->env != NULL)
			free_str_tab(data->env);
		rl_clear_history();//히스토리 초기화
	}
}

void	close_fds(t_command *cmds, bool close_backups)//fd 닫기
{
	if (cmds->io_fds != NULL)
	{
		if (cmds->io_fds->fd_in != -1)
			close(cmds->io_fds->fd_in);
		if (cmds->io_fds->fd_out != -1)
			close(cmds->io_fds->fd_out);
		if (close_backups != 0)
			restore_io(cmds->io_fds);
	}
	close_pipe_fds(cmds, NULL);
}

void	free_io(t_io_fds *io)//fd 구조체 해제
{
	if (io == NULL)
		return ;
	restore_io(io);
	if (io->heredoc_delimiter != NULL)
		free_ptr(io->heredoc_delimiter);
	if (io->infile != NULL)
		free_ptr(io->infile);
	if (io->outfile != NULL)
		free_ptr(io->outfile);
	if (io != NULL)
		free_ptr(io);
}

void	free_str_tab(char **tab)//이중포인터 외부 해제
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i] != NULL)
		{
			if (tab[i] != NULL)
			{
				free_ptr(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	free_ptr(void *ptr)//더블프리 방지용 조건
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
