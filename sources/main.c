/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:35:45 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/23 21:35:46 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

// accepts input from user for parsing and execution
void	minishell_loop(t_utils *utils)
{

	while (1)
	{
		utils->input = readline(READLINE_MSG);
		implement_utils(utils); //set utils->paths, cmds, pid, heredocs 
		//<old_position> implement_utils(utils); //check(utils->input); initialize utils and make sure paths
		if (!utils->input) //Error handling of readline
		{
			reset_utils(utils); //free cmds, paths
			free_utils(utils); //free pwd, old_pwd, envp
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		else if (utils->input[0] == '\0') //when user press ENTER only
		{
			reset_utils(utils); //free cmds, paths
			continue ;
		}
		add_history(utils->input); //buildin of readline lib, add input into command history list
		if (parse_input(utils)) // make linked list split, run command
			prepare_executor(utils);
		reset_utils(utils);
	}
}

// initialization of minishell
int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;

	if (argc != 1 || argv[1])
	{
		printf("No argument needed\n");
		exit(0);
	}
	init_signals();
	init_utils(&utils, envp);
	printf("\n%s\n\n", WELCOME_MSG);
	minishell_loop(&utils);
	free_utils(&utils);
	return (0);
}
