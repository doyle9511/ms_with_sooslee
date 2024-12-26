/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:33:45 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/26 15:11:31 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* is_n_flag:
인자가 -n 옵션 플래그인지 확인
-n, -nnnn, -nn 등의 변형을 true로 반환
--n, -nnnm, -n1234와 같이 다른 문자가 포함된 경우 false 반환
*/
static bool	is_n_flag(char *arg)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 0;
	if (arg[i] != '-')
		return (n_flag);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		n_flag = true;
	return (n_flag);
}

/* echo_print_args:
주어진 인자 배열을 표준출력(STDOUT)에 출력
*/
static void	echo_print_args(char **args, bool n_flag, int i)
{
	if (!args[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

/* echo_builtin:
echo 내장 명령어 실행: 주어진 문자열을 출력하고
-n 옵션에 따라 개행문자 추가 여부를 결정

echo hello world    # hello world\n
echo -n hello world # hello world (개행 없음)
echo -nnnn test     # test (개행 없음)
echo -n1 test       # -n1 test\n (-n1은 유효한 옵션이 아님)
*/
int	echo_builtin(t_data *data, char **args)
{
	int		i;
	bool	n_flag;

	(void)data;
	n_flag = false;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	echo_print_args(args, n_flag, i);
	return (EXIT_SUCCESS);
}
