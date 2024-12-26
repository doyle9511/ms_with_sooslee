/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:54:42 by donghwi2          #+#    #+#             */
/*   Updated: 2024/03/05 21:39:42 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		beggin_i;
	int		end_i;
	char	*t_s1;
	char	*rst_s;

	beggin_i = 0;
	end_i = ft_strlen(s1) - 1;
	t_s1 = (char *)s1;
	while (t_s1[beggin_i] != '\0' && ft_strchr(set, t_s1[beggin_i]) != NULL)
		beggin_i++;
	while (end_i >= 0 && ft_strchr(set, t_s1[end_i]) != NULL)
		end_i--;
	if (beggin_i > end_i)
		return (ft_strdup(""));
	rst_s = (char *)malloc(sizeof(char) * (end_i - beggin_i + 2));
	if (rst_s == NULL)
		return (NULL);
	i = -1;
	while (++i < end_i - beggin_i + 1)
		rst_s[i] = t_s1[beggin_i + i];
	rst_s[i] = '\0';
	return (rst_s);
}
/*
int	main(){
	char s1[] = "123456543217";
	char set[] = "123456";
	printf("%s\n", ft_strtrim(s1, set));
	return (0);
}//*/