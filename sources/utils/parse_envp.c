/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:35:26 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/25 17:49:05 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../headers/minishell.h"

void	check_pwd(t_data *data)
{
	char	**tmp;
	char	*var;

	if (!data->envp)
		data->envp = (char **) ft_calloc(2, sizeof(char *));
	if (!data->pwd || !data->old_pwd)
	{
		data->pwd = getcwd(NULL, 0);
		data->old_pwd = NULL;
		tmp = data->envp;
		var = ft_strjoin("PWD=", data->pwd);
		data->envp = add_var(data->envp, var);
		free_double_ptr((void **) tmp);
		free(var);
		var = ft_strjoin("OLDPWD=", data->old_pwd);
		tmp = data->envp;
		data->envp = add_var(data->envp, var);
		free_double_ptr((void **) tmp);
		free(var);
	}
}

/* gets hold of the present working directory
and old pwd from the copied envp (data->envp)
*/
int	find_pwd(t_data *data)
{
	int	i;

	i = 0;
	data->pwd = 0;
	data->old_pwd = 0;
	while (data->envp && data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PWD=", 4))
			data->pwd = ft_substr(data->envp[i],
					4, ft_strlen(data->envp[i]) - 4);
		else if (!ft_strncmp(data->envp[i], "OLDPWD=", 7))
			data->old_pwd = ft_substr(data->envp[i],
					7, ft_strlen(data->envp[i]) - 7);
		i++;
	}
	check_pwd(data);
	return (1);
}

/*
This function takes a char** parameter called envp,
 which is assumed to be an array of strings containing
environment variables. It iterates through the envp
 array, similar to the previous function.
Inside the loop, it looks for the environment
 variable "PATH" and returns its corresponding value
(the part after the equals sign) using ft_substr.
 If the "PATH" environment variable is not found,
  it returns
an empty string obtained by duplicating the
 null terminator character.
Note: It assumes that ft_substr is a custom
function to extract substrings.
*/
char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup("\0"));
}

/*
This function takes a t_data structure
 (likely containing utility variables) as a parameter.
It calls the find_path function, passing data->envp
 as an argument, to obtain the "PATH" environment
  variable value.
The returned value is stored in path_from_envp.
It then splits path_from_envp using ':' as the
delimiter to obtain individual paths, and
stores them in data->paths
using ft_split. After storing the paths, it frees
the memory allocated for path_from_envp.
It then iterates through each path in data->paths.
For each path, it checks if the last character
is not a slash ('/').
If it's not a slash, it appends a slash to the
path using ft_strjoin and assigns the updated
path to data->paths[i].
Finally, the function returns EXIT_SUCCESS,
indicating successful parsing of the environment variables.
*/
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
		if (ft_strncmp(&data->paths[i][ft_strlen(data->paths[i]) - 1],
			"/", 1) != 0)
		{
			tmp = ft_strjoin(data->paths[i], "/");
			free(data->paths[i]);
			data->paths[i] = tmp;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
