/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:31:58 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/26 17:44:42 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* join_strs:
두 문자열을 연결하고, 이전 문자열을 해제.
연결된 새 문자열 반환
*/
char	*join_strs(char *str, char *back_str)
{
	char	*temp;

	if (back_str == NULL)
		return (str);
	if (str == NULL)
		return (ft_strdup(back_str));
	temp = str;
	str = ft_strjoin(temp, back_str);
	free_ptr(temp);
	return (str);
}

/* add_detail_quotes:
에러 상세 설명에 따옴표를 추가할지 확인:
//예: "unset: `@': not a valid identifier"
//	export나 unset 명령어면 true
*/
static bool	add_detail_quotes(char *command)
{
	if (ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0)
		return (true);
	return (false);
}

/* errmsg_cmd:
프로그램 이름이 접두사로 붙은 에러 메시지를 표준 에러로 출력.
지정된 에러 번호로 반환.
*/
int	errmsg_cmd(char *command, char *detail, char *error_message, int error_nb)
{
	char	*message;
	bool	detail_quotes;

	detail_quotes = add_detail_quotes(command);
	message = ft_strdup("minishell: ");
	if (command != NULL)
	{
		message = join_strs(message, command);
		message = join_strs(message, ": ");
	}
	if (detail != NULL)
	{
		if (detail_quotes)
			message = join_strs(message, "`");
		message = join_strs(message, detail);
		if (detail_quotes)
			message = join_strs(message, "'");
		message = join_strs(message, ": ");
	}
	message = join_strs(message, error_message);
	ft_putendl_fd(message, STDERR_FILENO);
	free_ptr(message);
	return (error_nb);
}

/* errmsg:
특정 명령어와 관련없는 에러 메시지 출력.
파싱 단계의 문법 오류에 사용.
*/
void	errmsg(char *errmsg, char *detail, int quotes)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	msg = join_strs(msg, errmsg);
	if (quotes != '\0')
		msg = join_strs(msg, " `");
	else
		msg = join_strs(msg, ": ");
	msg = join_strs(msg, detail);
	if (quotes != '\0')
		msg = join_strs(msg, "'");
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
}

/* usage_message:
사용법 메시지 출력. 시작 인자가 잘못된 경우 사용.
*/
bool	usage_message(bool return_val)
{
	ft_putendl_fd("Usage: ./minishell", 2);
	ft_putendl_fd("Usage: ./minishell -c \"input line\"", 2);
	return (return_val);
}
