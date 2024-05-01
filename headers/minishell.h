/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:25:10 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/01 22:27:33 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
# include "utils.h"
# include "error.h"
# include "color.h"
# include "builtins.h"
# include "executor.h"
# include "parsing.h"

# include <sys/types.h>
# include <sys/wait.h>

int		parse_envp(t_data *data);
int		find_pwd(t_data *data);
int		free2_data(t_data *data);
int		event(void);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
char	**add_var(char **arr, char *str);

char	*delete_quotes_value(char *str);
char	*delete_quotes(char *str, char c);
char	*delete_quotes_export(char *str, char c);

int		parse_paths(t_data *data);

int		(*builtin_arr(char *str))(t_data *data, t_cmds *cmds);

int		g_status_code;

typedef enum e_status
{
	IN_CMD = 20,
	IN_HEREDOC = 40,
	CTRL_C = 130,
	CTRL_BS = 131,
	STOP_HEREDOC = 1,
}	t_g_status_code;

#endif
