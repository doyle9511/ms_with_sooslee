/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:44:22 by donghwi2          #+#    #+#             */
/*   Updated: 2024/03/07 05:31:09 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dest == NULL && size == 0)
		return (size + src_len);
	dest_len = ft_strlen(dest);
	i = 0;
	if (dest_len >= size)
		return (size + src_len);
	while (i + dest_len + 1 < size && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
/*
#include <stdio.h>
int	main(){
	char s1[] = "4321";
	char s2[] = "1234";
	int	num = ft_strlcat(0, s2, 0);
	printf("%s \n", s1);
	printf("%d \n", num);
	return 0;
}
//*/