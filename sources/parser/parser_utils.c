/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:34:45 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/25 16:58:14 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../headers/minishell.h"

// initializes a cmd struct
t_word	*init_cmd(t_word *start, t_cmds *new_cmd)
{
	t_word	*ptr;

	ptr = start;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type == CMD)
			new_cmd->command = ft_strdup(ptr->cont);
		else if (ptr->type == REDIR)
			new_cmd = push_redir(new_cmd, ptr);
		ptr = ptr->next;
	}
	new_cmd->args = init_args(start, new_cmd->command);
	if (!new_cmd->command)
		new_cmd->command = new_cmd->args[0];
	else
		new_cmd->args[0] = new_cmd->command;
	return (ptr);
}

// ints the argument list
char	**init_args(t_word *start, char *command)
{
	t_word	*ptr;
	int		count;
	char	**args;

	count = count_args(start, command);
	args = (char **)ft_calloc(count + 2, sizeof(char *));
	if (!args)
		ft_error(1);
	count = 1;
	if (!command)
		count = 0;
	ptr = start;
	while (args && ptr && ptr->type != PIPE)
	{
		if (ptr->type == ARG)
			args[count++] = ft_strdup(ptr->cont);
		ptr = ptr->next;
	}
	return (args);
}

// pushed command to list
void	push_cmd(t_data *data, t_cmds *cmd)
{
	t_cmds	*ptr;

	cmd->builtin = builtin_arr(cmd->command);
	last_in_redir(cmd);
	last_out_redir(cmd);
	ptr = data->cmds;
	if (!ptr)
		data->cmds = cmd;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = cmd;
		cmd->prev = ptr;
	}
}

// returns value of the variable var in data.envp
char	*ft_getenv(char *var, t_data *data)
{
	int		i;
	char	**value;
	char	*ret;

	i = -1;
	while (data->envp[++i])
	{
		value = ft_split(data->envp[i], '=');
		if (!value)
		{
			ft_error(1);
			return (0);
		}
		if (!ft_strcmp(var, value[0]))
		{
			if (value[1])
				ret = ft_strdup(value[1]);
			else
				ret = ft_calloc(1, sizeof(char));
			free_double_ptr((void **) value);
			return (ret);
		}
		free_double_ptr((void **) value);
	}
	return (ft_strdup(""));
}

// replace $? with the error code
char	*expand_err(char *cont, int *i)
{
	char	*err;

	err = ft_itoa(g_status_code);
	(*i) = (*i) + 2;
	cont = replace_env(cont, i, err, 1);
	if (!cont)
		return (0);
	(*i) = 0;
	return (cont);
}
