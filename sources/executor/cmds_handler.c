/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:32:32 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/23 21:32:35 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int	find_exec_error(char *cmd, int code)
{
	char	*temp;

	if (code == 1 && !access(cmd, X_OK)) //int access(const char *path, int mode);
	{
		exec_error(cmd, 4); //no permission to execute
		free(cmd);
		return (126);
	}
	if (code == 2)
	{
		temp = ft_substr(cmd, 0, ft_strlen(cmd) - 2);
		if (cmd[ft_strlen(cmd) - 1] == '/' // is the directory path
			&& access(temp, F_OK)) //and directory is not existed
		{
			free (temp);
			return (exec_error(cmd, 2)); //not path
		}
		free (temp);
		if (cmd[ft_strlen(cmd) - 1] != '/' //file or command path ==
					&& access(cmd, F_OK)) // command is not existed
			return (exec_error(cmd, 1));
	}
	return (exec_error(cmd, 0));
}

/*
The function find_cmd is responsible for finding
and executing a command. It takes two parameters: a t_cmds struct
pointer named cmd and a t_utils struct pointer named
utils. The function attempts to execute the command specified
by cmd->str[0] by searching for the command in the system's
 paths. It first checks if the command exists using the
access function with F_OK parameter. If the command is
found, execve is called to replace the current process with
the specified command. If the command is not found, the
function returns a value indicating that the command was not found.
*/
int	find_cmd(t_cmds *cmd, t_utils *utils)
{
	if (ft_strlen(cmd->command) == 0) //NULL cmd
		return (exec_error(cmd->command, 0)); //cmd not found
	if (is_directory(cmd->command)) //1 = exist, check directory exist by open it
		return (exec_error(cmd->command, 3)); // is a directory but not an executable file
	else if (cmd->command[ft_strlen(cmd->command) - 1] == '/') //directory path
		return (find_cmd_helper(cmd)); // only return 126 0r 127
	if (cmd->command[0] != '/' && cmd->command[0] != '.') //not a path command
	{
		if (loop_paths(utils, cmd) != 0) //combine path and cmd to execute cmd
			return (127); //cannot run any cmd in loop paths
	}
	else if (!access(cmd->command, F_OK) && (cmd->command[0] == '/' //file path starting / or .
			|| cmd->command[0] == '.')) // and cmd file exists
	{
		if (access(cmd->command, X_OK)) //not excutable
			return (exec_error(cmd->command, 4)); //message error
		execve(cmd->command, cmd->args, utils->envp); //run cmd
	}
	else if (access(cmd->command, F_OK)) //file is not exist
		return (find_exec_error(cmd->command, 1)); //mesasge
	return (find_exec_error(cmd->command, 0));
}

/* Inside the function,
it performs the following actions:
It checks if there are any
redirections specified by
calling check_redirections if
 cmd->redirections is not NUL.
If the command is a built-in
command (indicated by
cmd->builtin not being NULL), it calls the
corresponding built-in
command function and exits
with the return code of the
 command. If the command is not a built-in command
 and the command
string is not empty, it calls the find_cmd function to
find and execute the command.
Finally, it exits with the exit code
returned by find_cmd
or 0 if no command was executed.
*/
void	handle_cmd(t_cmds *cmd, t_utils *utils)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redirections && check_redirections(cmd))
	{
		reset_utils(utils);
		free_utils(utils);
		exit(1);
	}
	if (cmd->builtin != NULL)
	{
		exit_code = cmd->builtin(utils, cmd);//run built-in
		reset_utils(utils);
		free_utils(utils);
		exit(exit_code);
	}
	else if (cmd->command)
		exit_code = find_cmd(cmd, utils); //find cmd and run
	reset_utils(utils);
	free_utils(utils);
	exit(exit_code);
}

/*
if the command has a previous command (cmd->prev is not NULL),
 it uses dup2 function to duplicate the input file descriptor
(fd_in) to the standard input file descriptor (STDIN_FILENO).
If there is an issue with the duplication, it calls the
ft_error function with error code 4 and the utils struc
*/
/* It closes the read end of the pipe (end[0]). */
/*
If the command has a next command (cmd->next is not NULL),
it uses dup2 function to duplicate the write end of the pipe (end[1])
to the standard output file descriptor (STDOUT_FILENO). If
there is an issue with the duplication, it calls the ft_error
function with error code 4 and the utils struct.
// It closes the write end of the pipe (end[1]).
// If the command has a previous command, it closes the
input file descriptor (fd_in).
*/
void	dup_cmd(t_cmds *cmd, t_utils *utils, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		ft_error(4);
	close(end[0]);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		ft_error(4);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	handle_cmd(cmd, utils);
}

/*
The function single_cmd is responsible for handling a single
command. It takes two parameters: a
t_cmds struct pointer named cmd and
a t_utils struct pointer named utils. Inside the function, it
performs the following actions:
It calls call_expander to expand any variables or perform
command substitution in the command string.
If the command is a built-in command (specifically mini_cd,
mini_exit, mini_export, or mini_unset), it calls the
corresponding built-in command
WIFEXITED is a macro that checks whether a child
process has exited normally.
status is a variable that likely holds
the status information of a child process.
The WEXITSTATUS macro retrieves the exit
status of a child process.
*/
void	single_cmd(t_cmds *cmd, t_utils *utils)
{
	int	pid;
	int	status;
	int	exit_status;

	exit_status = -1;
	// to write heredoc files and set related parameters
	if (send_heredoc(utils, cmd) == EXIT_FAILURE)
		return ;
	//system call, 
	//create new process by duplicating the calling process
	pid = fork();//pid of the child process,
	if (pid < 0)
		ft_error(5);
	else if (pid == 0)// already in the child process to run the cmd
		handle_cmd(cmd, utils); //execute execve() succeed will replace child process
	// this allows cmd program can run inside the shell, external program not built-in
	if (cmd->builtin == m_export || cmd->builtin == m_cd
		|| cmd->builtin == m_exit || cmd->builtin == m_unset)
		p_builtins(utils, cmd); //check whether built-in cmd
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	if (g_status_code != STOP_HEREDOC && exit_status != -1)
		g_status_code = exit_status;
}
