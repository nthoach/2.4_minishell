/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:35:03 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/13 18:54:26 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// finds the last input redirection
void	last_in_redir(t_command *cmd)
{
	t_redir	*ptr;
	t_redir	*last;
	int		type;

	if (!cmd->redirections)
		return ;
	type = -1;
	ptr = cmd->redirections;
	while (ptr)
	{
		if (ptr->type == INPUT)
		{
			type = ptr->type;
			ptr->type = IGNORE;
			last = ptr;
		}
		ptr = ptr->next;
	}
	if (type != -1)
		last->type = type;
}

// finds the last output redirection
void	last_out_redir(t_command *cmd)
{
	t_redir	*ptr;
	t_redir	*last;
	int		type;

	if (!cmd->redirections)
		return ;
	type = -1;
	ptr = cmd->redirections;
	while (ptr)
	{
		if (ptr->type == WRITE || ptr->type == APPEND)
		{
			type = ptr->type;
			ptr->type = OPEN;
			last = ptr;
		}
		ptr = ptr->next;
	}
	if (type != -1)
		last->type = type;
}

// sorts redirection types
void	sort_redir(t_word *ptr, t_redir *redir)
{
	if (ptr->cont[0] == '<' && !ptr->cont[1])
		redir->type = INPUT;
	else if (ptr->cont[0] == '>' && !ptr->cont[1])
		redir->type = WRITE;
	else if (ptr->cont[0] == '<' && ptr->cont[1] == '<')
		redir->type = HEREDOC;
	else if (ptr->cont[0] == '>' && ptr->cont[1] == '>')
		redir->type = APPEND;
}

// adds redirection to list
t_command	*push_redir(t_command *cmd, t_word *ptr)
{
	t_redir	*r;
	t_redir	*redir;

	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redir)
	{
		err_all(1);
		return (0);
	}
	if (ptr->next->type == PATH)
		redir->path = ft_strdup(ptr->next->cont);
	else
		return (0);
	sort_redir(ptr, redir);
	r = cmd->redirections;
	if (!r)
		cmd->redirections = redir;
	else
	{
		while (r->next)
			r = r->next;
		r->next = redir;
	}
	redir->prev = r;
	return (cmd);
}
