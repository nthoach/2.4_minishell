/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:33:03 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/14 19:49:40 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mnsh.h"

int	wait_pipe(int *pid, int amount)
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
	if (g_status_code != HEREDOC_EXIT)
		g_status_code = exit_status;
	return (EXIT_SUCCESS);
}

int	ft_fork(t_data *data, int end[2], int fd_in, t_command *cmd)
{
	static int	i = 0;

	if (data->reset == true)
	{
		i = 0;
		data->reset = false;
	}
	data->pid[i] = fork();
	if (data->pid[i] < 0)
		err_all(5);
	if (data->pid[i] == 0)
		dup_cmd(cmd, data, end, fd_in);
	i++;
	return (EXIT_SUCCESS);
}

int	check_fd_heredoc(t_data *data, int end[2], t_command *cmd)
{
	int	fd_in;

	if (data->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd->filename_hd, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}
//  executing commands with pip

int	executor_pipe(t_data *data)
{
	int			end[2];
	int			fd_in;
	t_command	*curr_cmd;

	fd_in = STDIN_FILENO;
	curr_cmd = data->cmds;
	while (curr_cmd)
	{
		if (curr_cmd->next)
			if (pipe(end) < 0)
				return (!err_all(4));
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
	wait_pipe(data->pid, data->pipes);
	return (0);
}

// executing all the command from data
int	exec_all(t_data *data)
{
	signal(SIGQUIT, sigquit_handler);
	g_status_code = IN_CMD;
	if (data->pipes == 0)
		nopipe_cmd(data->cmds, data);
	else
	{
		data->pid = ft_calloc(data->pipes + 2, sizeof(int));
		if (!data->pid)
			return (err_all(1));
		if (executor_pipe(data))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
