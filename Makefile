NAME = minishell
FLAGS = -Wall -Werror -Wextra -g3
CC = cc

LIBFTP = libft/
PATHO = objs/
PATHS = sources/
PATHSL = sources/lexer/
PATHSP = sources/parser/
PATHSB = sources/builtins/
PATHSU = sources/utils/
PATHSE = sources/error/
PATHP = sources/pipex/
PATHEX = sources/executor/

sources	=	sources/main.c \
		sources/signal.c \
		sources/builtins/builtins.c \
		sources/builtins/m_cd.c \
		sources/builtins/m_echo.c \
		sources/builtins/m_env.c \
		sources/builtins/m_exit.c \
		sources/builtins/m_export.c \
		sources/builtins/m_pwd.c \
		sources/builtins/m_unset.c \
		sources/builtins/utils_builtins.c \
		sources/builtins/p_builtins.c \
		sources/utils/parse_envp.c \
		sources/utils/utils.c \
		sources/error/error_handling.c \
		sources/executor/redirection_check.c \
		sources/executor/executor.c \
		sources/executor/cmds_handler.c \
		sources/executor/exec_utils.c \
		sources/executor/heredoc.c \
		sources/executor/executor_utils.c \
		sources/lexer/input_validation.c \
		sources/lexer/lexer.c \
		sources/lexer/lexer_utils.c \
		sources/lexer/lexer_validation.c \
		sources/lexer/symbol_utils.c \
		sources/lexer/expand_env.c \
		sources/lexer/combine_quotes.c \
		sources/parser/parser.c \
		sources/parser/parser_utils.c \
		sources/parser/redirections.c \
		sources/parser/tokens.c

OBJS	=	$(addprefix $(PATHO), $(notdir $(patsubst %.c, %.o, $(sources))))

LIBFT	=	./libft/libft.a

HEADERS	=	./includes/builtins.h \
			./includes/color.h \
			./includes/error.h \
			./includes/executor.h \
			./includes/minishell.h \
			./includes/parsing.h \
			./includes/lexer.h \
			./includes/utils.h

READLINE_DIR = "/opt/homebrew/Cellar/readline/8.2.10"

READLINE_LIB = -L $(READLINE_DIR)/lib -L$(LIBFTP) -lft -lreadline -lhistory 


INCLUDES = -I./includes -I$(PATHP) -I$(LIBFTP) -I$(READLINE_DIR)/include

all: $(PATHO) $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(PATHO)
	@$(CC) $(FLAGS) $(LIBFT) $(OBJS) $(READLINE_LIB) -o $(NAME)

$(PATHO)%.o:: $(PATHSP)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}								in	$(PATHSP)${END}"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHS)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}								in	$(PATHS)${END}"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSL)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}								in	$(PATHSL)${END}"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSB)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}								in	$(PATHSB)${END}"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSU)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}								in	$(PATHSU)${END}"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHSE)%.c $(HEADERS)
	@echo "Compiling ${notdir $<}								in	$(PATHSE)${END}"
	@$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(PATHO)%.o:: $(PATHEX)%.c $(HEADERS)
	@echo "${notdir $<}											in	$(PATHEX)${END}"
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

re: fclean all

.PRECIOUS: $(PATHO)%.o
