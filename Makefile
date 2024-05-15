NAME = minishell
FLAGS = -Wall -Werror -Wextra -g3
CC = cc

LIBFTP = libft/
PATHO = objs/
PATHS = sources/
PATHSL = sources/lex/
PATHSP = sources/parse/
PATHSB = sources/built/
PATHSU = sources/utils/
PATHEX = sources/exec/
PATHINI = sources/init/

sources	=	sources/minishell.c \
		sources/init/signal_hand.c \
		sources/init/ini1_data.c \
		sources/built/built.c \
		sources/built/b_cd.c \
		sources/built/b_echo.c \
		sources/built/b_env.c \
		sources/built/b_exit.c \
		sources/built/b_export.c \
		sources/built/b_pwd.c \
		sources/built/b_unset.c \
		sources/built/u_built.c \
		sources/built/p_built.c \
		sources/utils/parse_envp.c \
		sources/utils/ini2_data.c \
		sources/utils/error_all.c \
		sources/exec/redir_check.c \
		sources/exec/exec_all.c \
		sources/exec/nopipe_cmd.c \
		sources/exec/exec1_utils.c \
		sources/exec/heredoc.c \
		sources/exec/exec2_utils.c \
		sources/lex/input_valid.c \
		sources/lex/lex.c \
		sources/lex/lex_utils.c \
		sources/lex/valid_split.c \
		sources/lex/symbol_utils.c \
		sources/lex/expand_env.c \
		sources/lex/handle_quote.c \
		sources/parse/parse_all.c \
		sources/parse/parse_help.c \
		sources/parse/redirec.c \
		sources/parse/tokens.c

OBJS	=	$(addprefix $(PATHO), $(notdir $(patsubst %.c, %.o, $(sources))))

LIBFT	=	./libft/libft.a

HEADERS	=	./headers/built.h \
			./headers/exec.h \
			./headers/mnsh.h \
			./headers/parse.h \
			./headers/lex.h

READLINE_DIR = /System/Volumes/Data/Users/honguyen/.brew/Cellar/readline/8.2.10

#READLINE_DIR = "/opt/homebrew/Cellar/readline/8.2.10"

READLINE_LIB = -L $(READLINE_DIR)/lib -L$(LIBFTP) -lft -lreadline -lhistory 


INCLUDES = -I./headers -I$(LIBFTP) -I$(READLINE_DIR)/include

all: $(PATHO) $(NAME)
	@echo "\n"
	@echo "  ***********************                                        ***********************"
	@echo "***********************.......Buidling ./minishell ...... Done!!...***********************"
	@echo "  ***********************                                        ***********************"
	@echo "\n"

$(NAME): $(LIBFT) $(OBJS) $(PATHO)
	@$(CC) $(FLAGS) $(LIBFT) $(OBJS) $(READLINE_LIB) -o $(NAME)

$(PATHO)%.o:: $(PATHSP)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}											in	$(PATHSP)${END}"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHS)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}											in	$(PATHS)${END}"
	@$(CC) -c $(FLAGS) $(INCLUDES)s $< -o $@

$(PATHO)%.o:: $(PATHSL)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}											in	$(PATHSL)${END}"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSB)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}											in	$(PATHSB)${END}"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSU)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}											in	$(PATHSU)${END}"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHEX)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}											in	$(PATHEX)${END}"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHINI)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}											in	$(PATHINI)${END}"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFTP)

$(PATHO):
	@mkdir $(PATHO)

clean:
	@rm -f $(OBJS)
	@rm -f .tmp*
	@rm -rf $(PATHO)
	@make fclean -C $(LIBFTP)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

run: re clean
	@make re
	@make clean
	@./$(NAME)

leaks: re clean
	@make re
	@make clean
	@valgrind --suppressions=valgrind_readline_leaks_ignore.txt --leak-check=full --trace-children=yes --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME)

re: fclean all

.PRECIOUS: $(PATHO)%.o
