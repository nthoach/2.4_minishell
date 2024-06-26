/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:35:55 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/14 19:49:40 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mnsh.h"

int	event(void)
{
	return (EXIT_SUCCESS);
}

// ctrl + c
void	sigint_handler(int sig)
{
	if (g_status_code != IN_HEREDOC)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (g_status_code == IN_CMD)
	{
		g_status_code = CTRL_C;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	else if (g_status_code == IN_HEREDOC)
	{
		g_status_code = HEREDOC_EXIT;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

// ctl+ '\'
void	sigquit_handler(int sig)
{
	if (g_status_code == IN_CMD)
	{
		g_status_code = CTRL_BS;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		ft_putstr_fd("Quit: ", STDERR_FILENO);
		ft_putnbr_fd(sig, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return ;
	}
}
