/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:31:18 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/25 17:48:29 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../headers/minishell.h"

void	print_lines(int i, char **str, int out)
{
	while (str[i])
	{
		ft_putstr_fd(str[i++], out);
		if (str[i])
			ft_putchar_fd(' ', out);
	}
}

/*checks if the echo function has -n flag so
that it removes new line so that it sets n_options
to true so that it does add newline
counter i will start from 1 after the command if there
is no flag (i.e 1) and will start from number
greater that 1 if there is a flag
for example: 4 if there is 3 flags

// this function iterates through the string and prints it
print_lines(i, cmds->args, STDOUT_FILENO);
// if there is no flag it will add a newline.
if (n_option == false)
	ft_putchar_fd('\n', STDOUT_FILENO);
*/
int	m_echo(t_data *data, t_cmds *cmds)
{
	int		i;
	int		j;
	bool	n_option;

	i = 1;
	n_option = false;
	(void) data;
	while (cmds->args[i] && cmds->args[i][0] == '-'
		&& cmds->args[i][1] == 'n')
	{
		j = 1;
		while (cmds->args[i][j] == 'n')
			j++;
		if (cmds->args[i][j] == '\0')
			n_option = true;
		else
			break ;
		i++;
	}
	print_lines(i, cmds->args, STDOUT_FILENO);
	if (n_option == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
