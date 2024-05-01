/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:32:14 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/25 16:57:24 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../headers/minishell.h"

// This function updates the data struct with the new paths
void	change_path(t_data *data)
{
	char	*tmp;

	tmp = ft_strdup(data->pwd);
	free(data->old_pwd);
	data->old_pwd = tmp;
	free(data->pwd);
	data->pwd = getcwd(NULL, 0);
}

size_t	equal_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*delete_quotes_value(char *str)
{
	char	**split_quotes;

	split_quotes = ft_split(str, '"');
	if (!split_quotes[1])
	{
		free_double_ptr((void **) split_quotes);
		split_quotes = ft_split(str, '\'');
	}
	free(str);
	str = ft_strjoin(split_quotes[0], split_quotes[1]);
	free_double_ptr((void **) split_quotes);
	return (str);
}

int	invalid_identifier(char *str, int f)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (f && i == (int) equal_sign(str) - 1)
			break ;
		if (str[i] == '|' || str[i] == '<' || str[i] == '>'
			|| str[i] == '[' || str[i] == ']' || str[i] == '='
			|| str[i] == '\'' || str[i] == '\"' || str[i] == ' '
			|| str[i] == ',' || str[i] == '.' || str[i] == '*'
			|| str[i] == ':' || str[i] == '/' || str[i] == '{'
			|| str[i] == '^' || str[i] == '%' || str[i] == '#'
			|| str[i] == '@' || str[i] == '!' || str[i] == '~'
			|| str[i] == '-' || str[i] == '?' || str[i] == '&'
			|| str[i] == '}' || str[i] == '+' || str[i] == '$' )
			return (1);
	}
	return (0);
}

int	check_valid_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
		|| c == '~'
		|| c == '=' || c == '-' || c == '?' || c == '&' || c == '*');
}
