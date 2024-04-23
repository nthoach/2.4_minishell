/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:55:14 by szerisen          #+#    #+#             */
/*   Updated: 2024/04/23 17:43:23 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

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
