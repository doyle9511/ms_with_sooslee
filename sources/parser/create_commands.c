/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:25:34 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/23 05:46:47 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prep_no_arg_commands(t_data *data)
{
	t_command	*cmd;

	if (!data || !data->cmd)
		return ;
	cmd = data->cmd;
	while (cmd && cmd->command)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof * cmd->args * 2);
			cmd->args[0] = ft_strdup(cmd->command);
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
	cmd = lst_last_cmd(data->cmd);
}

void	create_commands(t_data *data, t_token *token)//토큰화된 입력을 [실행가능한 명령어 구조체(t_commend)]로 변환하는 핵심적인 파서
{//execve에서 사용할 수 있는 형태로 형식 맞춰주는거
	t_token	*temp;

	temp = token;
	if (temp->type == END)
		return ;
	while (temp->next != NULL)
	{
		if (temp == token)
			lst_add_back_cmd(&data->cmd, lst_new_cmd(false));
		if (temp->type == WORD || temp->type == VAR)
			parse_word(&data->cmd, &temp);//명령어, 인자 처리 ex) command : "ls" / args : ["ls", "-l"]
		else if (temp->type == INPUT)
			parse_input(&data->cmd, &temp);// <
		else if (temp->type == TRUNC)
			parse_trunc(&data->cmd, &temp);// > 
		else if (temp->type == HEREDOC)
			parse_heredoc(data, &data->cmd, &temp);// <<
		else if (temp->type == APPEND)
			parse_append(&data->cmd, &temp);// >>
		else if (temp->type == PIPE)
			parse_pipe(&data->cmd, &temp);// |
		else if (temp->type == END)
			break ;
	}
	prep_no_arg_commands(data);//인자없는 명령어 형식 맞추기
}
