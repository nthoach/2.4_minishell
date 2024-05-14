/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:10:16 by honguyen          #+#    #+#             */
/*   Updated: 2024/05/13 19:03:08 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*join_split_str(char **split_str, char *new_str)
{
	char	*tmp;
	char	*add_space;
	int		i;

	tmp = ft_strdup(split_str[0]);
	i = 1;
	while (split_str[i])
	{
		new_str = tmp;
		add_space = ft_strjoin(new_str, " ");
		free(new_str);
		tmp = ft_strjoin(add_space, split_str[i]);
		free(add_space);
		i++;
	}
	new_str = tmp;
	return (new_str);
}

int	check_redir_helper(int type, t_redir *dir)
{
	int	fd;

	if (type == OPEN)
	{
		if (valid_byopenfile(dir))
			return (EXIT_FAILURE);
	}
	else if (type == WRITE || type == APPEND)
	{
		if (valid_outfile(dir))
			return (EXIT_FAILURE);
	}
	else if (type == IGNORE)
	{
		fd = open(dir->path, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: infile: No such file or directory\n",
				STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		close(fd);
	}
	return (EXIT_SUCCESS);
}

/*Additional Function command not found is added in error_handling.c*/
int	err_exec(char *str, int code)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, str, ft_strlen(str));
	if (code == 0)
		write(STDERR_FILENO, ": command not found\n", 21);
	else if (code == 1)
		write(STDERR_FILENO, ": No such file or directory\n", 29);
	else if (code == 2)
		write(STDERR_FILENO, ": Not a directory\n", 19);
	else if (code == 3)
		write(STDERR_FILENO, ": is a directory\n", 18);
	else if (code == 4)
		write(STDERR_FILENO, ": Permission denied\n", 21);
	if (code == 1 || code == 0)
		return (127);
	return (126);
}

int	exe_paths(t_data *data, t_command *cmd)
{
	int		i;
	char	*mycmd;

	i = 0;
	if (cmd->command[0] != '/' && cmd->command[0] != '.')
	{
		while (data->paths && data->paths[i])
		{
			mycmd = ft_strjoin(data->paths[i], cmd->command);
			if (!access(mycmd, F_OK))
			{
				execve(mycmd, cmd->args, data->envp);
				return (err_in_execve(mycmd, 1));
			}
			free(mycmd);
			i++;
		}
	}
	return (0);
}

int	is_directory(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
		return (0);
	else
	{
		closedir(dir);
		return (1);
	}
}
