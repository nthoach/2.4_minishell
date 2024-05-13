/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini2_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:12:06 by honguyen          #+#    #+#             */
/*   Updated: 2024/05/13 17:12:08 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// write data->paths, init cmds/pid/herdoc
int	ini2_data(t_data *data)
{
	parse_paths(data);
	data->cmds = NULL;
	data->pid = NULL;
	data->heredoc = false;
	return (1);
}

// frees memory associated with a cmd
void	free_cmd(t_cmds *cmd)
{
	t_redir	*ptr;
	t_redir	*del;

	if (cmd->hd_file_name)
		free(cmd->hd_file_name);
	if (cmd->args)
		free_double_ptr((void **)cmd->args);
	ptr = cmd->redirections;
	while (ptr)
	{
		del = ptr;
		ptr = ptr->next;
		if (del->path)
			free(del->path);
		free(del);
	}
	if (cmd)
		free(cmd);
}

// resets data variables
int	free2_data(t_data *data)
{
	t_cmds	*ptr;
	t_cmds	*del;

	ptr = data->cmds;
	while (ptr)
	{
		del = ptr;
		ptr = ptr->next;
		free_cmd(del);
	}
	if (data->input)
		free(data->input);
	if (data->pid)
		free(data->pid);
	data->reset = true;
	free_double_ptr((void **)data->paths);
	return (1);
}

// free pwd, old_pwd, envp
void	free1_data(t_data *data)
{
	if (data->pwd)
		free(data->pwd);
	if (data->old_pwd)
		free(data->old_pwd);
	free_double_ptr((void **)data->envp);
}

char	**ft_arrdup(char **arr)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(i + 1, sizeof(char *));
	if (!rtn)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_double_ptr((void **)rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}
