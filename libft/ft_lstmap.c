/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:09:58 by donghwi2          #+#    #+#             */
/*   Updated: 2024/03/07 03:46:12 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*first_list;
	t_list	*temp;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (new_list == NULL || lst == NULL || f == NULL)
		return (NULL);
	first_list = new_list;
	while (lst != NULL)
	{
		new_list->content = f(lst->content);
		temp = new_list;
		lst = lst->next;
		new_list = (t_list *)malloc(sizeof(t_list));
		if (new_list == NULL)
			return (NULL);
		if (lst == NULL)
			del(new_list);
		else
			temp->next = new_list;
	}
	temp->next = NULL;
	return (first_list);
}
