/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:56:17 by honguyen          #+#    #+#             */
/*   Updated: 2024/05/14 16:56:51 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <dirent.h>
# include "minishell.h"
# include "parsing.h"

int		(*builtin_fcn_name(char *str))(t_data *data, t_command *cmds);
int		b_echo(t_data *data, t_command *cmds);
int		b_cd(t_data *data, t_command *cmds);
int		b_pwd(t_data *data, t_command *cmds);
int		b_export(t_data *data, t_command *cmds);
int		b_unset(t_data *data, t_command *cmds);
int		b_env(t_data *data, t_command *cmds);
int		b_exit(t_data *data, t_command *cmds);

void	do_sort_env(t_data *data);
size_t	is_equalsign(char *str);
int		invalid_symbols(char *str, int f);
void	update_path(t_data *data);
void	update_pathinenv(t_data *data);
int		is_valid_symbol(char c);
int		error_invalid_symbols(char *identifier);
char	**del_env_var(char **arr, char *str);
char	**add_var(char **arr, char *str);
int		validate_symbol(char *str);
int		is_envvar_exist(t_data *data, char *str);
int		is_str_digit(char *str);
int		p_extract_path(t_data *data, char *str);
char	*find_path_ret(char *str, t_data *data);
void	p_builtins(t_data *data, t_command *cmd);

#endif
