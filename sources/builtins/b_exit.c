/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:31:35 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/13 18:54:26 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*if exit is passed without any argument it returns 0
checks if the second argument (str[1]) after the
 "exit" command is a valid numeric value.
*/
void	determine_exit_code(char **str)
{
	int	exit_code;

	if (!str[1])
		exit_code = 0;
	else if (is_str_digit(str[1]))
		exit_code = ft_atoi(str[1]);
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 255;
	}
	free_double_ptr((void **)str);
	exit(exit_code);
}

int	b_exit(t_data *data, t_command *cmds)
{
	char	**str;

	if (data->pipes == 0)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (cmds->args[1] && cmds->args[2] && is_str_digit(cmds->args[1]))
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (cmds->args[1] && !is_str_digit(cmds->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmds->args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		free2_data(data);
		free1_data(data);
		exit(255);
	}
	str = dup_arr(cmds->args);
	free2_data(data);
	free1_data(data);
	determine_exit_code(str);
	return (EXIT_SUCCESS);
}
