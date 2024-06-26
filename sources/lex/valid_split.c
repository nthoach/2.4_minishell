/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:34:11 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/14 19:49:40 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mnsh.h"

// checks for issues in input structure
int	valid_split(t_split *split)
{
	t_word	*ptr;

	ptr = split->first;
	if (ptr && ptr->type == PIPE)
		return (!err_parser(ptr));
	if (ptr && (split->last->type == PIPE || split->last->type == REDIR))
		return (!err_all(0));
	while (ptr)
	{
		if (ptr->type == REDIR && (ptr->next && (ptr->next->type == REDIR
					|| ptr->next->type == PIPE)))
			return (!err_parser(ptr));
		if (ptr->type == PIPE && (ptr->next && ptr->next->type == PIPE))
			return (!err_parser(ptr));
		ptr = ptr->next;
	}
	return (1);
}
