NAME = minishell
LIBFT = libft/libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRC = 	src/main.c \
	 	src/utils.c \
		src/lexer.c \
		src/split_shell.c \
		src/executor/path_cmd.c \
		src/executor/executor.c \
		src/builtin/builtin.c \
		src/builtin/ft_unset.c \
		src/builtin/utils_builtin.c \
		src/lexer_utils.c \
		src/parser.c \
		src/parser_redir.c \
		src/parser_quotes.c \
		src/parser_fd.c \
		src/signals/signals.c

LDFLAGS="-L/System/Volumes/Data/sgoinfre/goinfre/Perso/abarriga/homebrew/opt/readline/lib"
CPPFLAGS="-I/System/Volumes/Data/sgoinfre/goinfre/Perso/abarriga/homebrew/opt/readline/include"
LIB= -lreadline

AUTHOR = jlimones / abarriga
DATE = 21/03/2023

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

OBJ = $(SRC:.c=.o)

all: header $(NAME)
	@rm -rf .files_changed

header:
	@printf "%b" "$(OK_COLOR)"
	@echo "        ___  _____ ___  ___      _        "
	@echo "       /   |/ __  \|  \/  |     | |       "
	@echo "      / /| |\`' / /'| .  . | __ _| | _____ "
	@echo "     / /_| |  / /  | |\/| |/ _\` | |/ / _ \\"
	@echo "     \___  |./ /___| |  | | (_| |   <  __/"
	@echo "         |_/\_____/\_|  |_/\__,_|_|\_\___| v2"
	@echo
ifneq ($(HASH),)
	@printf "%b" "$(OBJ_COLOR)Name:	$(WARN_COLOR)$(NAME)@$(HASH)\n"
else
	@printf "%b" "$(OBJ_COLOR)Name:	$(WARN_COLOR)$(NAME)\n"
endif
	@printf "%b" "$(OBJ_COLOR)Author:	$(WARN_COLOR)$(AUTHOR)\n"
	@printf "%b" "$(OBJ_COLOR)Date: 	$(WARN_COLOR)$(DATE)\n\033[m"
	@printf "%b" "$(OBJ_COLOR)CC: 	$(WARN_COLOR)$(CC)\n\033[m"
	@printf "%b" "$(OBJ_COLOR)Flags: 	$(WARN_COLOR)$(FLAGS)\n\033[m"

$(NAME): ${OBJ}
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB) $(LIBFT) $(LDFLAGS) $(CPPFLAGS)
	@printf "%b" "$(OK_COLOR)" "minishell compilado\n"

skiperror:
	@$(CC) -o $(NAME) $(SRC)

clean: header
	@make clean -C libft
	@rm -f $(OBJ)

fclean: header clean
	@rm -f $(NAME)
	@make fclean -C libft
	@printf "%b" "$(OK_COLOR)" "fclean ejecutado correctamente\n"
	

re: fclean all
