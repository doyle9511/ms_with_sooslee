/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:40:21 by donghwi2          #+#    #+#             */
/*   Updated: 2025/01/01 22:26:27 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
signal.c 파일 적용예

Minishell $>_        # 입력 대기 중
^C                   # Ctrl+C 입력
Minishell $>_        # 새 프롬프트 출력

Minishell $>hello_   # 입력 중
^\                   # Ctrl+\ 입력
Minishell $>hello_   # 무시됨, 입력 계속

*/

void	signal_reset_prompt(int signo)//ctrl + c 함수 처리
{
	(void)signo;
	write(1, "\n", 1);//새 줄 출력
	rl_on_new_line();//readline에게 새 줄로 이동했음을 알림
	rl_replace_line("", 0);//현재 입력줄 비우기
	rl_redisplay();//프롬프트 재 출력
}

void	set_signal(void)//시그널 설정
{
	struct sigaction	act;

	ignore_sigquit();//ctrl + \ 무시 설정
	ft_memset(&act, 0, sizeof(act));//sigaction구조체 초기화
	act.sa_handler = &signal_reset_prompt;//ctrl + c 핸들러 설정
	sigaction(SIGINT, &act, NULL);//SIGINT에 핸들러 연결
}

void	signal_print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

void	ignore_sigquit(void)//ctrl + \ 무시
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;// 시그널 무시 설정
	sigaction(SIGQUIT, &act, NULL);// SIGQUIT에 적용
}
