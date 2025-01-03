/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:08:32 by donghwi2          #+#    #+#             */
/*   Updated: 2024/03/07 05:33:07 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*t_b;

	t_b = (char *)big;
	i = 0;
	if (little[0] == '\0')
		return (t_b);
	while (i < len && t_b[i] != '\0')
	{
		j = 0;
		while (t_b[i + j] == little[j] && i + j + 1 <= len && t_b[i] != '\0')
		{
			if (little[j + 1] == '\0')
				return (t_b + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(){
	char *s1 = "012345678";
	char *s2 = "012345678";
	char *ptr = ft_strnstr(s1, s2, 9);
	printf("%s \n", ptr);
	return 0;
}//*/