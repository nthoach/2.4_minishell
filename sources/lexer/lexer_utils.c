/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:11:09 by honguyen          #+#    #+#             */
/*   Updated: 2024/05/14 19:49:40 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mnsh.h"

// creates new word
t_word	*create_word(char *c, int type)
{
	t_word	*word;

	word = (t_word *)ft_calloc(1, sizeof(t_word));
	if (!word)
	{
		err_all(1);
		return (0);
	}
	word->type = type;
	word->cont = ft_strdup(c);
	return (word);
}

// pushes word to list
int	push_word(t_split *split, char *c, int type)
{
	t_word	*word;

	word = create_word(c, type);
	if (!word)
		return (0);
	word->index = split->cmds;
	word->next = 0;
	word->prev = split->last;
	if (split->cmds == 0)
		split->first = word;
	else
		split->last->next = word;
	split->last = word;
	split->cmds++;
	return (1);
}

char	*expand_env_quotes(t_word *word, int *i, t_data *data)
{
	if (word->cont[(*i)] == '\"')
	{
		(*i)++;
		while (word->cont[(*i)] && word->cont[(*i)] != '\"')
		{
			if (word->cont[(*i)] == '$')
			{
				if (word->cont[(*i) + 1] && word->cont[(*i) + 1] == '?')
					word->cont = expand_err(word->cont, i);
				else
					found_env(word->cont, i, word, data);
				return (word->cont);
			}
			else
				(*i)++;
		}
		if (word->cont[(*i)] == '\"')
			(*i)++;
	}
	return (word->cont);
}

int	found_env_helper(t_word *word, char *old, int *i)
{
	int		j;
	int		len;
	char	*temp;

	len = 0;
	j = (*i);
	if (old[j + 1] && old[j + 1] == '$')
	{
		temp = ft_itoa(getpid());
		(*i) = (*i) + 2;
		word->cont = replace_env(old, i, temp, 1);
		(*i) = 0;
		return (-1);
	}
	while (old[++j] && !is_space(old[j]) && old[j] != '$'
		&& !is_valid_symbol(old[j]))
		len++;
	if (!len)
	{
		(*i) = (*i) + 2;
		return (-1);
	}
	return (len);
}
