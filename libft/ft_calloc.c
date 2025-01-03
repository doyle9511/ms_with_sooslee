/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:49:30 by donghwi2          #+#    #+#             */
/*   Updated: 2024/03/07 04:35:44 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = (void *)malloc((nmemb) * size);
	if (ptr == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		((char *)ptr)[i] = '\0';
		i++;
	}
	return (ptr);
}
