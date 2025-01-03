/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:43:50 by donghwi2          #+#    #+#             */
/*   Updated: 2024/03/05 03:40:02 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*t_str;

	t_str = (char *)str;
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (t_str[i] == c)
		{
			return (t_str + i);
		}
		i--;
	}
	return (NULL);
}
