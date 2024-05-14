/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:57:25 by honguyen          #+#    #+#             */
/*   Updated: 2024/05/13 19:22:31 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include "builtins.h"
# include "executor.h"
# include "parsing.h"

# include <sys/types.h>
# include <sys/wait.h>

# define WELCOME_MSG	"Welcome to minishell"
# define HEREDOC_MSG	"\033[1;34m> \033[0m"
# define READLINE_MSG	"\e[38;5;212mminishell\033[34m$ \033[0m"

int		ini2_data(t_data *data);
char	**dup_arr(char **arr);
void	free1_data(t_data *data);
void	ini1_data(t_data *data, char **envp);

int		parse_envp(t_data *data);
int		find_pwd(t_data *data);
int		free2_data(t_data *data);
int		event(void);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
char	**add_var(char **arr, char *str);

//char	*delete_quotes_value(char *str);
//char	*delete_quotes(char *str, char c);
//char	*delete_quotes_export(char *str, char c);

int		parse_paths(t_data *data);

int		(*builtin_fcn_name(char *str))(t_data *data, t_command *cmds);

int		g_status_code;

typedef enum e_status
{
	IN_CMD = 20,
	IN_HEREDOC = 40,
	CTRL_C = 130,
	CTRL_BS = 131,
	HEREDOC_EXIT = 1,
}	t_g_status_code;

int		err_parser(t_word *ptr);
int		err_token_invalid(char *c);
int		err_token(t_data *data, int code);
int		err_all(int error);

typedef enum e_err_code
{
	ERR_SEMICOL,
	ERR_BACKSLASH,
	ERR_QUOTES,
	ERR_PIPE,
	ERR_G,
	ERR_GG,
	ERR_L,
	ERR_LL,
	ERR_NL,
}	t_err_code;

#endif
