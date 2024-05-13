/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:34:52 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/13 17:11:33 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// sorts tokens to list of commands
int	split2cmds(t_split *split, t_data *data)
{
	t_word	*ptr;
	t_cmds	*new_cmd;

	ptr = split->first;
	while (ptr)
	{
		new_cmd = (t_cmds *)ft_calloc(1, sizeof(t_cmds));
		if (!new_cmd)
			return (!ft_error(1));
		ptr = init_cmd(ptr, new_cmd);
		if (!new_cmd || !new_cmd->args)
			return (0);
		push_cmd(data, new_cmd);
		if (ptr && ptr->type == PIPE)
			ptr = ptr->next;
	}
	return (1);
}

int	count_pipes(t_data *data)
{
	t_cmds	*ptr;
	int		count;

	count = 0;
	ptr = data->cmds;
	while (ptr)
	{
		ptr = ptr->next;
		count++;
	}
	return (count - 1);
}

// print data for visualization
// void	print_data(t_data *data)
// {
// 	t_cmds	*c_ptr;
// 	int		i;
// 	t_redir	*r_ptr;

// 	c_ptr = data->cmds;
// 	while (c_ptr)
// 	{
// 		printf("cmd: %s\n", c_ptr->command);
// 		i = 0;
// 		while (c_ptr->args[i])
// 			printf("arg: %s\n", c_ptr->args[i++]);
// 		r_ptr = c_ptr->redirections;
// 		while (r_ptr)
// 		{
// 			printf("%i - %s\n", r_ptr->type, r_ptr->path);
// 			r_ptr = r_ptr->next;
// 		}
// 		c_ptr = c_ptr->next;
// 	}
// }

int	count_args(t_word *start, char *command)
{
	t_word	*ptr;
	int		count;

	ptr = start;
	count = 0;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type == ARG)
			count++;
		ptr = ptr->next;
	}
	if (!command)
		count--;
	return (count);
}

// checks input and parses to a data struct
// valid_input invalid with ';' '&' '\'
// split_input
int	parse_all(t_data *data)
{
	t_split	*split;
	int		sorted;

	if (valid_input(data->input) == 0)
		return (0);
	split = input2split(data->input, data);
	if (split == 0)
		return (0);
	sorted = split2cmds(split, data);
	free_split(split);
	data->pipes = count_pipes(data);
	return (sorted);
}
