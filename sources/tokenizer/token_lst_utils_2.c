/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 02:12:59 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/23 05:59:28 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	link_extremities(t_token *to_del, t_token *temp, t_token *insert)
{
	while (temp != to_del)
		temp = temp->next;
	insert->prev = temp->prev;
	temp->prev->next = insert;
	while (insert->next)
		insert = insert->next;
	temp->next->prev = insert;
	insert->next = temp->next;
}

t_token	*insert_lst_between(t_token **head, t_token *to_del, t_token *insert)
{
	t_token	*temp;

	temp = *head;
	if (temp == NULL)
		*head = insert;
	else if (temp == to_del)
	{
		*head = insert;
		insert->next = temp->next;
		if (temp->next != NULL)
			temp->next->prev = insert;
	}
	else
		link_extremities(to_del, temp, insert);
	free_ptr(to_del->str);
	free_ptr(to_del);
	return (insert);
}
