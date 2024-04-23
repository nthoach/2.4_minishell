/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:34:25 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/23 21:34:27 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

// frees split structure
void	free_split(t_split *split)
{
	t_word	*del;
	t_word	*ptr;

	if (!split)
		return ;
	ptr = split->first;
	while (ptr)
	{
		free(ptr->cont);
		del = ptr;
		ptr = ptr->next;
		free(del);
	}
	free(split);
}

// splits input to space-separated words
int	split_words(char *input, t_split *split)
{
	int	i;

	i = 0;
	while (input[i])
	{
		skip_space(input, &i);
		if (input[i])
		{
			if (!define_word(input, &i, split))
				return (0);
		}
	}
	return (1);
}

// splits input, checks errors, expands env,
// combines quotes, and sorts type
t_split	*split_input(char *input, t_utils *utils)
{
	t_split	*split;

	split = (t_split *)ft_calloc(1, sizeof(t_split)); //memory allocation
	if (!split) //fail to allocated
	{
		ft_error(1);
		return (0);
	}
	// make linked list and check error case for input
	// up to here, word type will be 4 types: PIPE, REDIR, QUOTE, STR 
	if (!split_words(input, split) || !check_split(split)) // cut down words and add to linked list
	{
		free_split(split);
		return (0);
	}
	//check expansion in STR word and replace expansion accordingly
	if (!expand_env(split, utils) || !combine_quotes(split))
	{
		free_split(split);
		return (0);
	}
	sort_split(split);
	return (split);
}

// sorts the type of word
void	sort_split(t_split *split)
{
	t_word	*ptr;

	ptr = split->first;
	if (ptr && ptr->type == STR)
		ptr->type = CMD;
	while (ptr)
	{
		if (ptr->prev && ptr->type == STR && ptr->prev->type == PIPE)
			ptr->type = CMD;
		else if (ptr->prev && ptr->prev->type == REDIR)
			ptr->type = PATH;
		else if (ptr->type == STR)
			ptr->type = ARG;
		ptr = ptr->next;
	}
}
