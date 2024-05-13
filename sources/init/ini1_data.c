/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini1_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:04:11 by honguyen          #+#    #+#             */
/*   Updated: 2024/05/13 17:10:37 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
