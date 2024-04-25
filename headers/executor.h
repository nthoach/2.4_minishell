/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:23:48 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/25 17:48:19 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "parsing.h"
# include "minishell.h"

// check_redirections
int				check_redirections(t_cmds *cmd);
int				handle_outfile(t_redir *redir);
int				handle_open(t_redir *redir);

// executor
int				prepare_executor(t_data *data);
int				executor(t_data *data);
int				pipe_wait(int *pid, int amount);
int				exec_error(char *str, int code);

// handle_cmd
int				find_cmd(t_cmds *cmd, t_data *data);
void			handle_cmd(t_cmds *cmd, t_data *data);
void			dup_cmd(t_cmds *cmd, t_data *data,
					int end[2], int fd_in);
void			single_cmd(t_cmds *cmd, t_data *data);
int				loop_paths(t_data *data, t_cmds *cmd);
int				find_exec_error(char *cmd, int code);
int				is_directory(char *path);

// heredoc
int				send_heredoc(t_data *data, t_cmds *cmd);

//executor_data
int				check_redir_helper(int type, t_redir *dir);

//exec_data
int				find_cmd_helper(t_cmds *cmd);

#endif
