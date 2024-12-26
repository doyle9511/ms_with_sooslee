/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:45:58 by donghwi2          #+#    #+#             */
/*   Updated: 2024/03/05 15:21:55 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*str;
	char	*temp_s;

	temp_s = (char *)s;
	len = ft_strlen(temp_s);
	str = (char *)malloc((sizeof(char) * (len + 1)));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = f(i, temp_s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>
int	main(){
	char str[] = "aaaaaa";
	printf("%s \n", ft_strmapi(str, &ft_test));
	return (0);
}//*/