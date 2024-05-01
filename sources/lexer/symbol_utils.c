/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:34:35 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/25 16:58:14 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../headers/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}


int	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}


void	skip_quotes(int *i, char *input)
{
	int	quote;

	quote = input[*i];
	(*i) = (*i) + 1;
	while (input[*i] && input[*i] != quote)
		(*i) = (*i) + 1;
	if (input[*i] && input[*i] == quote)
		(*i) = (*i) + 1;
}
