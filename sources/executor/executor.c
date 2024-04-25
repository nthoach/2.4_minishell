/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:33:03 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/25 21:20:49 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../headers/minishell.h"

// pipe_wait: This function waits for child processes to complete execution
// when multiple pipes are used. It takes an
// array of process IDs (pid) and the number of
// processes (amount) as arguments. It iterates over the array of process
// IDs and waits for each child process to exit using waitpid.
//  After all child processes have exited, it checks the exit
// status using WIFEXITED and sets the global g_global.error_num
// to the exit status of the last child process. It returns EXIT_SUCCESS.

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

// ft_fork: This function is responsible for forking a
// child process and executing the command. It takes a t_data pointer,
// an array of
// pipe file descriptors (end), the input file descriptor (fd_in),
// and a t_cmds pointer as arguments. It first checks if the data->reset
// flag is set and resets the static variable i if necessary.
// Then, it forks a child process using fork and assigns the process ID to
// data->pid[i]. If the fork fails, it calls ft_error to handle the error.
//  In the child process, it calls the dup_cmd function to
// set up the necessary file descriptors and execute the command.
// Finally, it increments i and returns EXIT_SUCCESS.
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
/*
check_fd_heredoc: This function checks the file
descriptor for input redirection. It takes a t_data pointer,
an array of pipe file descriptors (end), and a t_cmds pointer
as arguments. If the data->heredoc flag is set,
indicating the use of a here document, it closes
the read end of the pipe (end[0]), opens the here document
file in read-only mode, and returns the file descriptor.
Otherwise, it returns end[0], which represents the
standard input file descriptor.
*/

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
