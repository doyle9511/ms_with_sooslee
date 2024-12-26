/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:05:51 by donghwi2          #+#    #+#             */
/*   Updated: 2024/03/05 00:31:03 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	char	*ptr;
	int		str_len;
	int		i;

	i = 0;
	str_len = ft_strlen(string);
	ptr = (char *)malloc((str_len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < str_len)
	{
		ptr[i] = string[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
#include <stdio.h>
int	main(){
	char s1[] = "12345678";
	char *s2 = ft_strdup(s1);
	printf("%s \n", s2);
	return 0;
}//*/