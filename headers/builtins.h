/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:56:17 by honguyen          #+#    #+#             */
/*   Updated: 2024/05/13 16:56:21 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <dirent.h>
# include "minishell.h"
# include "parsing.h"

//builtins
int		(*builtin_arr(char *str))(t_data *data, t_cmds *cmds);
int		m_echo(t_data *data, t_cmds *cmds);
int		m_cd(t_data *data, t_cmds *cmds);
int		m_pwd(t_data *data, t_cmds *cmds);
int		m_export(t_data *data, t_cmds *cmds);
int		m_unset(t_data *data, t_cmds *cmds);
int		m_env(t_data *data, t_cmds *cmds);
int		m_exit(t_data *data, t_cmds *cmds);

void	sorted_env(t_data *data);
size_t	equal_sign(char *str);
int		invalid_identifier(char *str, int f);
void	change_path(t_data *data);
void	update_path_to_env(t_data *data);
int		check_valid_identifier(char c);
int		error_invalid_identifier(char *identifier);
char	**del_var(char **arr, char *str);
void	parent_export(t_data *data, t_cmds *cmds);
char	**add_var(char **arr, char *str);
int		check_parameter(char *str);
int		variable_exist(t_data *data, char *str);
int		is_str_digit(char *str);
int		p_specific_path(t_data *data, char *str);
char	*find_path_ret(char *str, t_data *data);
void	p_builtins(t_data *data, t_cmds *cmd);

#endif
