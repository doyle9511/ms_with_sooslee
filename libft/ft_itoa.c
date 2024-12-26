/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:20:43 by donghwi2          #+#    #+#             */
/*   Updated: 2024/03/04 22:01:53 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_count_digit(long long n)
{
	int			digit_num;
	long long	temp_n;
	char		*str;

	digit_num = 0;
	temp_n = n;
	while (temp_n > 0)
	{
		temp_n /= 10;
		digit_num++;
	}
	str = (char *)malloc(sizeof(char) * (digit_num + 2));
	if (str == NULL)
		return (NULL);
	str[digit_num + 1] = '\0';
	while (digit_num >= 1)
	{
		str[digit_num] = n % 10 + '0';
		n /= 10;
		digit_num--;
	}
	str[0] = '-';
	return (str);
}

char	*ft_if_zero(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	if (str == NULL)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int			i;
	int			sign;
	char		*str;
	long long	long_n;

	long_n = (long long)n;
	sign = 1;
	if (long_n == 0)
		str = ft_if_zero();
	else
	{
		if (long_n < 0)
		{
			sign *= -1;
			long_n *= -1;
		}
		str = ft_count_digit(long_n);
		i = -1;
		if (sign == 1)
		{
			while (str[++i] != '\0')
				str[i] = str[i + 1];
		}
	}
	return (str);
}

/*
#include <stdio.h>
int	main(){
	char * str = ft_itoa(1);
	printf("%s \n", str);
	free(str);
	return (0);
}
*/
