/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:31:15 by alexa             #+#    #+#             */
/*   Updated: 2024/12/16 17:15:01 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
[사용자 입력]을 words / seperator(|, >> 등)토큰으로 나눔
- 문자열의 각 문자를 검사하여 구분자인지 단어인지 판단하고, 연결 리스트(t_token)에 저장
- 닫히지 않은 따옴표 오류 확인하고, 따옴표 규칙에 따라 특수문자 평가:
	- 따옴표 없음: 모든 특수문자 평가
	- 작은따옴표('): 모든 평가 방지
	- 큰따옴표("): 대부분 평가 방지 (단, 변수("$HOME")는 평가됨)
*/

int	tokenization(t_data *data, char *str)
{
	int	i;
	int	end;
	int	start;
	int	status;

	i = -1;
	start = 0;
	end = ft_strlen(str);
	status = DEFAULT;
	while (++i <= end)
	{
		status = set_status(status, str, i);
		if (status == DEFAULT)//따옴표 안쪽이 아니면->
			start = save_word_or_sep(&i, str, start, data);//token list에 type분류해서 add
	}
	if (status != DEFAULT)
	{
		if (status == DQUOTE)
			errmsg("unexpected EOF while looking for matching", "\"", true);
		else if (status == SQUOTE)
			errmsg("unexpected EOF while looking for matching", "\'", true);
		errmsg("syntax error", "unexpected end of file", false);
		return (1);
	}
	return (0);
}
