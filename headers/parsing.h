/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:25:15 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/01 22:34:10 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include "lexer.h"

# define CLEAR_SCREEN_SEQ "\033[2J\033[H"

typedef struct s_cmds	t_cmds;
typedef struct s_redir	t_redir;

typedef struct s_data
{
	struct s_cmds	*cmds;
	char			*input;
	char			**envp;
	char			**paths;
	char			*pwd;
	char			*old_pwd;
	int				pipes;
	int				*pid;
	bool			reset;
	bool			heredoc;
}	t_data;

typedef struct s_cmds
{
	char			*command;
	char			**args;
	t_redir			*redirections;
	struct s_cmds	*next;
	int				(*builtin)(t_data *, t_cmds *);
	struct s_cmds	*prev;
	char			*hd_file_name;
}	t_cmds;

typedef struct s_redir
{
	char			*path;
	int				type;
	int				fd;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef enum e_redir
{
	IGNORE,
	OPEN,
	APPEND,
	WRITE,
	INPUT,
	HEREDOC,
}	t_redir_type;

int		is_space(char c);
int		is_quote(char c);
int		is_symbol(char c);
void	skip_quotes(int *i, char *input);
void	skip_space(char *input, int *j);
void	push_cmd(t_data *data, t_cmds *cmd);

int		valid_input(char *input);
int		split2cmds(t_split *split, t_data *data);
char	**init_args(t_word *start, char *command);
int		parse_all(t_data *data);
char	*ft_getenv(char *var, t_data *data);
t_word	*init_cmd(t_word *ptr, t_cmds *new_cmd);
char	*expand_err(char *cont, int *i);
char	*replace_env(char *str, int *i, char *exp, int len);
void	last_in_redir(t_cmds *cmd);
void	last_out_redir(t_cmds *cmd);
t_cmds	*push_redir(t_cmds *cmd, t_word *ptr);
int		count_args(t_word *start, char *command);

#endif
