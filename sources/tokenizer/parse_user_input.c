/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:12:55 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/02 00:15:45 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	input_is_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	parse_user_input(t_data *data)
{
	if (data->user_input == NULL)//ctrl + D등으로 NULL일때
		exit_builtin(data, NULL);//exit(빌트인함수) 실행
	else if (ft_strcmp(data->user_input, "\0") == 0)//엔터만 입력했을 때
		return (false);
	else if (input_is_space(data->user_input) != 0)//공백을 입력했을 때
		return (true);
	add_history(data->user_input);//엔터나 공백 말고 유효한 명령어는 input값 연결리스트에 저장
	if (tokenization(data, data->user_input) == FAILURE)//token화 완료
		return (false);
	if (data->token->type == END)//바로 끝나면 false (필요없을지도?)
		return (false);
	if (check_if_var(&data->token) == FAILURE)
		return (false);
	var_expander(data, &data->token);// $ 들어있을 떄, 조건 살펴보고 $USER 처럼 들어오면 value 저장후 삭제
	handle_quotes(data);// 조건에 따라 따옴표 지우기
	create_commands(data, data->token);//token을 이용하여 t_command 명령어 구조체 생성
	return (true);
}
