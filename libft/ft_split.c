/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:25:11 by donghwi2          #+#    #+#             */
/*   Updated: 2024/03/06 05:52:40 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_word(char const *s, char c)
{
	int	i;
	int	word_num;

	i = 0;
	word_num = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			word_num++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (word_num);
}

char	**ft_malloc(char const *str, char c)
{
	int		i;
	char	**dstr;

	i = ft_count_word(str, c);
	dstr = malloc(sizeof(*dstr) * (i + 1));
	if (dstr == 0)
		return (0);
	return (dstr);
}

int	ft_count_next(char const *str, char c, int i)
{
	int	cnt;

	cnt = 0;
	while (str[i] == c && str[i] != '\0')
		i++;
	while (str[i] != c && str[i] != '\0' )
	{
		cnt++;
		i++;
	}
	return (cnt);
}

char	**ft_free(char **dstr, int i)
{
	int	j;

	j = 0;
	while (j < i && dstr[j] != 0)
	{
		free(dstr[j]);
		j++;
	}
	free(dstr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**dstr;

	k = 0;
	i = -1;
	dstr = ft_malloc(s, c);
	if (dstr == NULL)
		return (NULL);
	while (++i < ft_count_word(s, c))
	{
		j = 0;
		dstr[i] = malloc(ft_count_next(s, c, k) + 1);
		if (dstr[i] == NULL)
			return (ft_free(dstr, i));
		while (s[k] != '\0' && s[k] == c)
			k++;
		while (s[k] != '\0' && s[k] != c)
			dstr[i][j++] = s[k++];
		dstr[i][j] = '\0';
	}
	dstr[i] = 0;
	return (dstr);
}
/*
#include <stdio.h>
int	main()
{
	char ptr[] = "";
	char **dptr;

	dptr = ft_split("", 'z');
	for(int i = 0; i < 1; i++){
		printf("%s\n", dptr[i]);
	}
	return (0);
}//*/
