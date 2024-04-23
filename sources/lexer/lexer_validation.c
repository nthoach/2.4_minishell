/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:34:11 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/23 21:34:13 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

//checks for issues in input structure
int	check_split(t_split *split)
{
	t_word	*ptr;

	ptr = split->first;
	if (ptr && ptr->type == PIPE)
		return (!parser_error(ptr));
	if (ptr && (split->last->type == PIPE || split->last->type == REDIR))
		return (!ft_error(0));
	while (ptr)
	{
		if (ptr->type == REDIR
			&& (ptr->next && (ptr->next->type == REDIR
					|| ptr->next->type == PIPE)))
			return (!parser_error(ptr));
		if (ptr->type == PIPE
			&& (ptr->next && ptr->next->type == PIPE))
			return (!parser_error(ptr));
		ptr = ptr->next;
	}
	return (1);
}
