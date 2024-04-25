/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:35:36 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/25 17:41:01 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
		free_double_ptr((void **) cmd->args);
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
int	reset_data(t_data *data)
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

// free memory on exit
void	free_data(t_data *data)
{
	if (data->pwd)
		free(data->pwd);
	if (data->old_pwd)
		free(data->old_pwd);
	free_double_ptr((void **) data->envp);
}

// duplicates the passed string
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
			free_double_ptr((void **) rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}
