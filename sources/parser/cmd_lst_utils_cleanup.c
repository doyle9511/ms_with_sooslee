/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_utils_cleanup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:21:24 by alexa             #+#    #+#             */
/*   Updated: 2024/12/09 17:31:29 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_delone_cmd(t_command *lst, void (*del)(void *))
{
	if (lst->command)
		(*del)(lst->command);
	if (lst->args)
		free_str_tab(lst->args);
	if (lst->pipe_fd)
		(*del)(lst->pipe_fd);
	if (lst->io_fds)
		free_io(lst->io_fds);
	(*del)(lst);
}

void	lst_clear_cmd(t_command **lst, void (*del)(void *))
{
	t_command	*temp;

	temp = NULL;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		lst_delone_cmd(*lst, del);
		*lst = temp;
	}
}
