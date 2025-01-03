/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooslee <sooslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:50:41 by sooslee           #+#    #+#             */
/*   Updated: 2024/12/31 14:53:30 by sooslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_free(char **temp)
{
	int i;
	
	i = 0;
	while(temp[i])
	{
		free(temp[i]);
		i ++;
	}
	free(temp);
}