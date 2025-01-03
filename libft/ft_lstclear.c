/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:58:15 by donghwi2          #+#    #+#             */
/*   Updated: 2024/03/07 00:13:04 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
/*
#include <stdio.h>
int	main(){
	t_list *lst1;
	t_list *lst2;
	t_list *lst3;
	lst1->content = "123"; lst1->next = lst2;
	lst2->content = "456"; lst2->next = lst3;
	lst3->content = "789"; lst3->next = NULL;
	t_list *lst[3] = {lst1, lst2, lst3};
	ft_lstclear(lst, del);
}//*/