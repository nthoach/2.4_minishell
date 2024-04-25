/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:35:45 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/25 21:11:13 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../headers/minishell.h"

void	minishell_loop(t_data *data)
{
	printf("\n%s\n\n", WELCOME_MSG);
	while (1)
	{
		data->input = readline(READLINE_MSG);
		ini2_data(data);
		if (!data->input) 
		{
			reset_data(data);
			free_data(data);
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		else if (data->input[0] == '\0')
		{
			reset_data(data);
			continue ;
		}
		add_history(data->input);
		if (parse_input(data))
			prepare_executor(data);
		reset_data(data);
	}
}

// initialization of minishell
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1])
	{
		printf("just run:'./minishell' !! No argument needed !!\n");
		exit(0);
	}
	init_signals();
	ini1_data(&data, envp);
	minishell_loop(&data);
	free_data(&data);
	return (0);
}
