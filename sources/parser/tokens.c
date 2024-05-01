/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:35:14 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/01 22:30:20 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../headers/minishell.h"

// adds redirection to list
static int	add_redir(t_split *split, char *input, int *i)
{
	int	success;

	if (input[(*i) + 1] && input[(*i) + 1] == input[(*i)])
	{
		if (input[(*i)] == '>')
			success = push_word(split, ">>", REDIR);
		else
			success = push_word(split, "<<", REDIR);
		(*i) = (*i) + 2;
	}
	else
	{
		if (input[(*i)] == '>')
			success = push_word(split, ">", REDIR);
		else
			success = push_word(split, "<", REDIR);
		(*i) = (*i) + 1;
	}
	return (success);
}

// adds quote to list
static int	add_quote(t_split *split, char *input, int *i)
{
	int		start;
	int		len;
	char	*str;

	start = (*i);
	while (input[(*i)] && !is_space(input[(*i)]) && !is_symbol(input[(*i)]))
	{
		if (is_quote(input[(*i)]))
			skip_quotes(i, input);
		else
			(*i)++;
	}
	len = (*i) - start;
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (!ft_error(1));
	len = -1;
	while ((++len + start) < (*i))
		str[len] = input[start + len];
	if (!push_word(split, str, QUOTE))
		return (0);
	free(str);
	return (1);
}

int	str_len(int *i, char *input)
{
	int	len;
	int	start;

	start = (*i);
	while (input[(*i)] && !(is_symbol(input[(*i)]) || is_space(input[(*i)])))
	{
		if (is_quote(input[(*i)]))
			skip_quotes(i, input);
		else
			(*i)++;
	}
	len = (*i) - start;
	return (len);
}

// adds unspecified string to list
static int	add_str(t_split *split, char *input, int *i)
{
	int		start;
	int		len;
	int		k;
	char	*str;

	start = (*i);
	len = str_len(i, input);
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (!ft_error(1));
	k = -1;
	while ((start + (++k)) < (*i))
		str[k] = input[start + k];
	if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		len = push_word(split, str, QUOTE);
	else
		len = push_word(split, str, STR);
	if (!len)
		return (0);
	free(str);
	return (1);
}

// define: PIPE, REDIR, QUOTE, STR
int	define_word(char *input, int *i, t_split *split)
{
	int	success;

	success = 0;
	if (input[(*i)] == '|')
	{
		success = push_word(split, "|", PIPE);
		(*i)++;
	}
	else if (input[(*i)] == '>' || input[(*i)] == '<')
		success = add_redir(split, input, i);
	else if (is_quote(input[(*i)]))
		success = add_quote(split, input, i);
	else
		success = add_str(split, input, i);
	return (success);
}
