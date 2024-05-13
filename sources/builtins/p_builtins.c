/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:32:05 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/13 17:13:24 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	p_export(t_data *data, t_cmds *cmds)
{
	char	**tmp;
	int		i;

	i = 1;
	if (!cmds->args[1] || cmds->args[1][0] == '\0')
		return ;
	else
	{
		while (cmds->args[i])
		{
			if (!check_parameter(cmds->args[i]) && !variable_exist(data,
					cmds->args[i]) && !invalid_identifier(cmds->args[i], 1))
			{
				tmp = add_var(data->envp, cmds->args[i]);
				free_double_ptr((void **)data->envp);
				data->envp = tmp;
			}
			else if ((invalid_identifier(cmds->args[i], 1)
					|| check_parameter(cmds->args[i])))
				return ;
			i++;
		}
	}
	return ;
}

void	p_exit(t_data *data, t_cmds *cmds)
{
	int	exit_code;

	if (cmds->args[1] && cmds->args[2] && is_str_digit(cmds->args[1]))
		return ;
	if (!is_str_digit(cmds->args[1]))
		exit_code = 255;
	else if (!cmds->args[1])
		exit_code = 0;
	else if (is_str_digit(cmds->args[1]))
		exit_code = ft_atoi(cmds->args[1]);
	else
		exit_code = 255;
	free2_data(data);
	free1_data(data);
	exit(exit_code);
}

void	p_unset(t_data *data, t_cmds *cmds)
{
	char	**temp;

	if (!cmds->args[1] || invalid_identifier(cmds->args[1], 0)
		|| equal_sign(cmds->args[1]) != 0)
		return ;
	temp = del_var(data->envp, cmds->args[1]);
	free_double_ptr((void **)data->envp);
	data->envp = temp;
}

void	p_cd(t_data *data, t_cmds *cmds)
{
	int		ret;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	if (!cmds->args[1])
		ret = p_specific_path(data, "HOME=");
	else if (ft_strncmp(cmds->args[1], "-", 1) == 0)
		ret = p_specific_path(data, "OLDPWD=");
	else if (cmds->args[1][0] == '~')
	{
		tmp = find_path_ret("HOME=", data);
		tmp1 = ft_substr(cmds->args[1], 1, ft_strlen(cmds->args[1]) - 1);
		tmp2 = ft_strjoin(tmp, tmp1);
		ret = chdir(tmp2);
		free(tmp);
		free(tmp1);
		free(tmp2);
	}
	else
		ret = chdir(cmds->args[1]);
	if (ret != 0)
		return ;
	change_path(data);
	update_path_to_env(data);
}

void	p_builtins(t_data *data, t_cmds *cmd)
{
	if (cmd->builtin == m_export)
		p_export(data, cmd);
	if (cmd->builtin == m_cd)
		p_cd(data, cmd);
	if (cmd->builtin == m_exit)
		p_exit(data, cmd);
	if (cmd->builtin == m_unset)
		p_unset(data, cmd);
}
