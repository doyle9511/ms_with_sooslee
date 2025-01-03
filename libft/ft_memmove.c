/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:02:11 by donghwi2          #+#    #+#             */
/*   Updated: 2024/03/04 23:38:19 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int		i;
	size_t	t_i;

	if (dest < src)
	{
		i = 0;
		t_i = (size_t)i;
		while (t_i < n)
		{
			((char *)dest)[t_i] = ((char *)src)[t_i];
			t_i++;
		}
	}
	else if (dest > src)
	{
		i = n - 1;
		while (i >= 0)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i--;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
int	main(){
	char str1[] = "12345678";
	char str2[] = "abcdefgh";
	char *str3 = ft_memmove(str1, str1 + 2, 4);
	printf("%s \n", str3);
	return (0);
}
*/