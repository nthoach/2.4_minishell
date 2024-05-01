/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:33:03 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/01 23:01:12 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../headers/minishell.h"

int	pipe_wait(int *pid, int amount)
{
	int	i;
	int	status;
	int	exit_status;

	i = 0;
	status = 0;
	while (i < amount)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	if (g_status_code != STOP_HEREDOC)
		g_status_code = exit_status;
	return (EXIT_SUCCESS);
}

int	ft_fork(t_data *data, int end[2], int fd_in, t_cmds *cmd)
{
	static int	i = 0;

	if (data->reset == true)
	{
		i = 0;
		data->reset = false;
	}
	data->pid[i] = fork();
	if (data->pid[i] < 0)
		ft_error(5);
	if (data->pid[i] == 0)
		dup_cmd(cmd, data, end, fd_in);
	i++;
	return (EXIT_SUCCESS);
}

int	check_fd_heredoc(t_data *data, int end[2], t_cmds *cmd)
{
	int	fd_in;

	if (data->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd->hd_file_name, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}
//  executing commands with pip

int	executor(t_data *data)
{
	int		end[2];
	int		fd_in;
	t_cmds	*curr_cmd;

	fd_in = STDIN_FILENO;
	curr_cmd = data->cmds;
	while (curr_cmd)
	{
		if (curr_cmd->next)
			if (pipe(end) < 0)
				return (!ft_error(4));
		send_heredoc(data, curr_cmd);
		if (ft_fork(data, end, fd_in, curr_cmd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		close(end[1]);
		if (curr_cmd->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(data, end, curr_cmd);
		if (curr_cmd->next)
			curr_cmd = curr_cmd->next;
		else
			break ;
	}
	pipe_wait(data->pid, data->pipes);
	return (0);
}

//executing all the command from data
int	exec_all(t_data *data)
{
	signal(SIGQUIT, sigquit_handler);
	g_status_code = IN_CMD;
	if (data->pipes == 0)
		single_cmd(data->cmds, data);
	else
	{
		data->pid = ft_calloc(data->pipes + 2, sizeof(int));
		if (!data->pid)
			return (ft_error(1));
		if (executor(data))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
