/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:35:26 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/25 17:30:50 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../headers/minishell.h"

void	ini1_data(t_data *data, char **envp)
{
	rl_catch_signals = 0;
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	data->cmds = 0;
	data->paths = 0;
	data->pwd = 0;
	data->old_pwd = 0;
	data->pipes = 0;
	data->pid = 0;
	data->envp = 0;
	data->reset = false;
	if (*envp != 0)
		data->envp = ft_arrdup(envp);
	find_pwd(data);
}
