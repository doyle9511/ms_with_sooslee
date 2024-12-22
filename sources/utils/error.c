/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:31:58 by donghwi2          #+#    #+#             */
/*   Updated: 2024/12/23 06:01:29 by donghwi2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* join_strs:
*	Joins two strings together, freeing the previous string.
*	Returns the new concatenated string. Or NULL if an error occured.
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
*	Checks whether to add quotes around the error detail:
*	i.e. "unset: `@': not a valid identifier"
*	Returns true if the command is export or unset,
*	false if not.
*/
static bool	add_detail_quotes(char *command)
{
	if (ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0)
		return (true);
	return (false);
}

/* errmsg_cmd:
*	Prints an error message to the standard error, prefixed with the
*	program name.
*	Returns with the specified error number.
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
*	Prints an error message that is unrelated to a specific command.
*	Used in parsing phase for syntax errors.
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
*	Prints a usage message. Used if start-up arguments are invalid.
*/
bool	usage_message(bool return_val)
{
	ft_putendl_fd("Usage: ./minishell", 2);
	ft_putendl_fd("Usage: ./minishell -c \"input line\"", 2);
	return (return_val);
}
