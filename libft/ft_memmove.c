/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:57:19 by mcombeau          #+#    #+#             */
/*   Updated: 2024/12/09 19:35:36 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dp;
	const char	*sp;

	if (src == dst)
		return (dst);
	dp = (char *)dst;
	sp = (const char *)src;
	if (sp < dp && sp + len > dp)
		while (len--)
			*(dp + len) = *(sp + len);
	else
	{
		while (len--)
		{
			*dp = *sp;
			sp++;
			dp++;
		}
	}
	return (dst);
}
