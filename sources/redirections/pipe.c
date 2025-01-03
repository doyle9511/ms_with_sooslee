/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:13:34 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/23 06:19:32 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* close_pipe_fds:
모든 명령어의 파이프 fd를 닫습니다.
건너뛸 명령어를 지정할 수 있음:
- 부모 프로세스: skip_cmd로 NULL 지정하여 모든 파이프 fd 닫음
- 자식 프로세스: 자신의 파이프 fd를 실수로 닫지 않도록 자신의 명령어를 skip_cmd로 지정
*/
void	close_pipe_fds(t_command *cmds, t_command *skip_cmd)
{
	while (cmds)
	{
		if (cmds != skip_cmd && cmds->pipe_fd)
		{
			close(cmds->pipe_fd[0]);
			close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}

/* create_pipes:
명령어 리스트에서 파이프로 연결된 각 명령어에 대해 파이프 세트 생성
*/
bool	create_pipes(t_data *data)
{
	int			*fd;
	t_command	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->pipe_output || (tmp->prev && tmp->prev->pipe_output))
		{
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
			{
				free_data(data, false);
				return (false);
			}
			tmp->pipe_fd = fd;
		}
		tmp = tmp->next;
	}
	return (true);
}

/* set_pipe_fds:
이 명령어의 파이프 파일 디스크립터를 설정합.
- 이전 명령어가 현재 명령어로 파이프되어 있다면, 이전 명령어의 읽기 끝을 입력으로 설정
- 현재 명령어가 다음 명령어로 파이프된다면, 파이프의 쓰기 끝을 출력으로 설정
pipe_fd[0] = 파이프의 읽기 끝
pipe_fd[1] = 파이프의 쓰기 끝
파이프 fd 설정되면 true 반환
*/
bool	set_pipe_fds(t_command *cmds, t_command *c)
{
	if (!c)
		return (false);
	if (c->prev && c->prev->pipe_output)
		dup2(c->prev->pipe_fd[0], STDIN_FILENO);
	if (c->pipe_output)
		dup2(c->pipe_fd[1], STDOUT_FILENO);
	close_pipe_fds(cmds, c);
	return (true);
}
