/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:39:03 by donghwi2          #+#    #+#             */
/*   Updated: 2024/03/05 02:38:47 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*temp_str;

	temp_str = (char *)str;
	while (*temp_str != '\0')
	{
		if (*temp_str == (unsigned char)c)
			return (temp_str);
		temp_str++;
	}
	if (c == 0)
		return (temp_str);
	return (NULL);
}
