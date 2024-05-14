/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:32:22 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/13 18:36:11 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	err_all(int error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error == 0)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n",
			STDERR_FILENO);
	else if (error == 1)
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
	else if (error == 2)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n",
			STDERR_FILENO);
	else if (error == 4)
		ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	else if (error == 5)
		ft_putstr_fd("Failed to fork\n", STDERR_FILENO);
	else if (error == 6)
		ft_putstr_fd("outfile: Error\n", STDERR_FILENO);
	else if (error == 7)
		ft_putstr_fd("infile: No such file or directory\n", STDERR_FILENO);
	else if (error == 8)
		ft_putendl_fd("Path does not exist", STDERR_FILENO);
	else if (error == 9)
		ft_putendl_fd("Path does not exist", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	err_parser(t_word *ptr)
{
	if (ptr->type == PIPE)
		err_token(0, ERR_PIPE);
	else if (ptr->type == REDIR && ft_strlen(ptr->cont) == 1)
	{
		if (ptr->cont[0] == '>')
			err_token(0, ERR_G);
		else if (ptr->cont[0] == '<')
			err_token(0, ERR_L);
	}
	else if (ptr->type == REDIR && ft_strlen(ptr->cont) == 2)
	{
		if (ptr->cont[0] == '>')
			err_token(0, ERR_GG);
		else if (ptr->cont[0] == '<')
			err_token(0, ERR_LL);
	}
	else
		err_token(0, ERR_NL);
	return (EXIT_FAILURE);
}

int	err_token_invalid(char *c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	ft_putstr_fd(c, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	err_token(t_data *data, int code)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
		STDERR_FILENO);
	if (code == ERR_G)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (code == ERR_GG)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	else if (code == ERR_L)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (code == ERR_LL)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (code == ERR_PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	if (data)
		free2_data(data);
	return (EXIT_FAILURE);
}
