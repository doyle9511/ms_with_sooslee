/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 23:31:44 by donghwi2          #+#    #+#             */
/*   Updated: 2024/03/04 21:15:01 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	c2;

	c2 = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		((unsigned char *)str)[i] = c2;
		i++;
	}
	return (str);
}
