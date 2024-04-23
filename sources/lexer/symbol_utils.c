/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:34:35 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/23 21:34:37 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

//checks if character is a space
int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

//checks if character is a quote
int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

//checks if character is a marker symbol
int	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

//if input[i] is a quote, we jump i to the input[i] character
// after the close of the quote
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

//if input[i] is a space, we jump i to the input[i] character
// that is not a space or 0 if end of array
void	skip_space(char *input, int *j)
{
	int	i;

	i = *j;
	while (input[i] && is_space(input[i]))
		i++;
	*j = i;
}
