/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:35:26 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/18 10:43:43 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mnsh.h"

void	check_pwd(t_data *data)
{
	char	**tmp;
	char	*var;

	if (!data->envp)
		data->envp = (char **)ft_calloc(2, sizeof(char *));
	if (!data->pwd || !data->old_pwd)
	{
		data->pwd = getcwd(NULL, 0);
		data->old_pwd = NULL;
		tmp = data->envp;
		var = ft_strjoin("PWD=", data->pwd);
		data->envp = add_var(data->envp, var);
		free_double_ptr((void **)tmp);
		free(var);
		var = ft_strjoin("OLDPWD=", data->old_pwd);
		tmp = data->envp;
		data->envp = add_var(data->envp, var);
		free_double_ptr((void **)tmp);
		free(var);
	}
}

int	find_pwd(t_data *data)
{
	int	i;

	i = 0;
	data->pwd = 0;
	data->old_pwd = 0;
	while (data->envp && data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PWD=", 4))
			data->pwd = ft_substr(data->envp[i], 4, ft_strlen(data->envp[i])
					- 4);
		else if (!ft_strncmp(data->envp[i], "OLDPWD=", 7))
			data->old_pwd = ft_substr(data->envp[i], 7, ft_strlen(data->envp[i])
					- 7);
		i++;
	}
	check_pwd(data);
	return (1);
}

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup("\0"));
}

int	parse_paths(t_data *data)
{
	char	*path_from_envp;
	int		i;
	char	*tmp;

	path_from_envp = find_path(data->envp);
	data->paths = ft_split(path_from_envp, ':');
	free(path_from_envp);
	i = 0;
	while (data->paths[i])
	{
		if (ft_strncmp(&data->paths[i][ft_strlen(data->paths[i]) - 1], "/",
			1) != 0)
		{
			tmp = ft_strjoin(data->paths[i], "/");
			free(data->paths[i]);
			data->paths[i] = tmp;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
