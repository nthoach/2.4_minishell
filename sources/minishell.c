/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:35:45 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/18 15:59:48 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/mnsh.h"

void	minishell_loop(t_data *data)
{
	ft_printf("\n%s\n\n", WELCOME_MSG);
	while (1)
	{
		data->input = readline(READLINE_MSG);
		ini2_data(data);
		if (data->input == 0)
		{
			free2_data(data);
			free1_data(data);
			ft_printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		else if (data->input[0] == '\0')
		{
			free2_data(data);
			continue ;
		}
		add_history(data->input);
		if (parse_all(data))
			exec_all(data);
		free2_data(data);
	}
}

// initialization of minishell
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1])
	{
		ft_printf("just run:'./minishell' !! No argument needed !!\n");
		exit(0);
	}
	ini1_data(&data, envp);
	minishell_loop(&data);
	free1_data(&data);
	return (0);
}
