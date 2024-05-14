/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:56:51 by honguyen          #+#    #+#             */
/*   Updated: 2024/05/13 19:03:08 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "parsing.h"
# include "minishell.h"

// redirections
int				valid_redir(t_command *cmd);
int				valid_outfile(t_redir *redir);
int				valid_byopenfile(t_redir *redir);

// executor
int				exec_all(t_data *data);
int				executor_pipe(t_data *data);
int				wait_pipe(int *pid, int amount);
int				err_exec(char *str, int code);

// exe_cmd
int				find_exe_cmd(t_command *cmd, t_data *data);
void			check_exe_cmd(t_command *cmd, t_data *data);
void			dup_cmd(t_command *cmd, t_data *data,
					int end[2], int fd_in);
void			nopipe_cmd(t_command *cmd, t_data *data);
int				exe_paths(t_data *data, t_command *cmd);
int				err_in_execve(char *cmd, int code);
int				is_directory(char *path);

// heredoc
int				send_heredoc(t_data *data, t_command *cmd);

int				check_redir_helper(int type, t_redir *dir);

//exec_data
int				find_exe_cmd_helper(t_command *cmd);

#endif
