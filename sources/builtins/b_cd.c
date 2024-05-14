/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:31:09 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/13 18:54:26 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*find_path_ret(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (data->envp && data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], str, ft_strlen(str)))
			return (ft_substr(data->envp[i], ft_strlen(str),
					ft_strlen(data->envp[i]) - ft_strlen(str)));
		i++;
	}
	return (NULL);
}

int	specific_path(t_data *data, char *str)
{
	char	*tmp;
	int		ret;

	ret = -1;
	tmp = find_path_ret(str, data);
	if (tmp)
	{
		ret = chdir(tmp);
		free(tmp);
	}
	if (ret != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}

void	update_pathinenv(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->envp && data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", data->pwd);
			free(data->envp[i]);
			data->envp[i] = tmp;
		}
		else if (!ft_strncmp(data->envp[i], "OLDPWD=", 7) && data->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", data->old_pwd);
			free(data->envp[i]);
			data->envp[i] = tmp;
		}
		i++;
	}
}

int	cd_helper(t_data *data, t_command *cmds)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	int		ret;

	if (cmds->args[1][0] == '~')
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
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmds->args[1], STDERR_FILENO);
		perror(" ");
	}
	return (ret);
}

int	b_cd(t_data *data, t_command *cmds)
{
	int	ret;

	if (!cmds->args[1])
		ret = specific_path(data, "HOME=");
	else if (ft_strncmp(cmds->args[1], "-", 1) == 0)
		ret = specific_path(data, "OLDPWD=");
	else
		ret = cd_helper(data, cmds);
	if (ret != 0)
		return (EXIT_FAILURE);
	update_path(data);
	update_pathinenv(data);
	return (EXIT_SUCCESS);
}
