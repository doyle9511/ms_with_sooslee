# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sooslee <sooslee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/07 11:56:21 by donghwi2          #+#    #+#              #
#    Updated: 2024/12/26 23:18:02 by sooslee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= gcc
CFLAGS	= -Werror -Wextra -Wall -gdwarf-4 -g -fsanitize=address
SRC_PATH = ./sources/
OBJ_PATH = ./objects/
INC_PATH = ./includes/
SRC		= 	main.c \
			utils/init_data.c \
			env/env.c \
			env/env_set.c \
			tokenizer/parse_user_input.c \
			tokenizer/tokenization.c \
			tokenizer/tokenization_utils.c \
			tokenizer/check_if_var.c \
			tokenizer/token_lst_utils.c \
			tokenizer/token_lst_utils_2.c \
			expansion/var_expander.c \
			expansion/var_expander_utils.c \
			expansion/identify_var.c \
			expansion/quotes_handler.c \
			expansion/quotes_remover.c \
			expansion/recover_value.c \
			expansion/replace_var.c \
			parser/create_commands.c \
			parser/parse_word.c \
			parser/fill_args_echo.c \
			parser/fill_args_echo_utils.c \
			parser/fill_args_default.c \
			parser/parse_input.c \
			parser/parse_trunc.c \
			parser/parse_append.c \
			parser/parse_heredoc.c \
			parser/parse_heredoc_utils.c \
			parser/parse_pipe.c \
			parser/cmd_lst_utils.c \
			parser/cmd_lst_utils_cleanup.c \
			builtins/export_builtin.c \
			builtins/unset_builtin.c \
			builtins/cd_builtin.c \
			builtins/env_builtin.c \
			builtins/pwd_builtin.c \
			builtins/echo_builtin.c \
			builtins/exit_builtin.c \
			execution/execute.c \
			execution/execute_cmd.c \
			execution/execute_utils.c \
			execution/parse_path.c \
			redirections/pipe.c \
			redirections/file_io.c \
			utils/error.c \
			utils/cleanup.c \
			signals/signal.c
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INC		= -I $(INC_PATH) -I $(LIBFT_PATH)
#INC = -I $(INC_PATH) -I $(LIBFT_PATH) -I /opt/homebrew/Cellar/readline/8.2.13/include

LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/builtins
	mkdir -p $(OBJ_PATH)/tokenizer
	mkdir -p $(OBJ_PATH)/expansion
	mkdir -p $(OBJ_PATH)/parser
	mkdir -p $(OBJ_PATH)/testing
	mkdir -p $(OBJ_PATH)/env
	mkdir -p $(OBJ_PATH)/execution
	mkdir -p $(OBJ_PATH)/utils
	mkdir -p $(OBJ_PATH)/redirections
	mkdir -p $(OBJ_PATH)/signals

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) -lreadline
# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) -L /opt/homebrew/Cellar/readline/8.2.13/lib -lreadline -lhistory

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all re clean fclean