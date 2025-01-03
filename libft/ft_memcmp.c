/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:44:47 by donghwi2          #+#    #+#             */
/*   Updated: 2024/03/05 01:17:34 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i + 1 < n && (ss1)[i] == (ss2)[i])
		i++;
	return ((ss1)[i] - (ss2)[i]);
}
/*
#include <stdio.h>
int	main(){
	char s1[] = {1 ,0 ,0 ,1 };
	char s2[] = {0 ,0 ,0 ,2 };
	int	num = ft_memcmp(s1, s2, 1);
	printf("%d \n", num);
	return 0;
}//*/