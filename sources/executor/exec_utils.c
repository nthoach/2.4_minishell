/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:32:41 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/25 16:58:14 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../headers/minishell.h"

int	find_cmd_helper(t_cmds *cmd)
{
	char	*tmp;
	char	*tmp1;

	tmp1 = ft_strtrim(cmd->command, "/");
	if (cmd->command[0] == '/')
		tmp = ft_strjoin("/", tmp1);
	else
		tmp = ft_strdup(tmp1);
	free(tmp1);
	if (!access(tmp, F_OK)) //command file exist but end with '\'
	{
		free(tmp);
		return (exec_error(cmd->command, 2)); //why?? return (0) instead
	}
	else //command file is not exist
	{
		free(tmp);
		return (exec_error(cmd->command, 1)); // no file or directory
	}
}
