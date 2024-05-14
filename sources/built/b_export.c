/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:31:42 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/14 19:49:40 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mnsh.h"

int	is_envvar_exist(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], str, is_equalsign(data->envp[i])) == 0)
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

/*check not valid symbols.*/
int	validate_symbol(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (EXIT_FAILURE);
	if (is_equalsign(str) == 0)
		return (EXIT_FAILURE);
	if (str[0] == '=')
		return (EXIT_FAILURE);
	while (str[i] != '=')
	{
		if (is_valid_symbol(str[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

/* copies the existing environment variables (arr) and
 adding a new variable (str) at the end of the copied list */
char	**whileloop_add_var(char **env, char **rtn, char *str)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (env[i + 1] == NULL)
		{
			rtn[i] = ft_strdup(str);
			rtn[i + 1] = ft_strdup(env[i]);
		}
		else
			rtn[i] = ft_strdup(env[i]);
		if (rtn[i] == NULL)
		{
			free_double_ptr((void **)rtn);
			return (rtn);
		}
		i++;
	}
	if (env[0] == NULL)
		rtn[0] = ft_strdup(str);
	return (rtn);
}

/*
it takes arr and adds str and return rtn which is composed of both
it allocates memory for the additional variable and return it
*/
char	**add_var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(i + 2, sizeof(char *));
	if (!rtn)
	{
		err_all(1);
		return (NULL);
	}
	i = 0;
	whileloop_add_var(arr, rtn, str);
	return (rtn);
}

/* if the command export is passed without any
arguments we just return env (acts as env)
if there is a second argument it will go inside the while loop
variable exist will check if str exist in env variable */
int	b_export(t_data *data, t_command *cmds)
{
	char	**tmp;
	int		i;

	i = 1;
	if (!cmds->args[1] || cmds->args[1][0] == '\0')
		do_sort_env(data);
	else
	{
		while (cmds->args[i])
		{
			if (!validate_symbol(cmds->args[i]) && !is_envvar_exist(data,
					cmds->args[i]) && !invalid_symbols(cmds->args[i], 1))
			{
				tmp = add_var(data->envp, cmds->args[i]);
				free_double_ptr((void **)data->envp);
				data->envp = tmp;
			}
			else if ((invalid_symbols(cmds->args[i], 1)
					|| validate_symbol(cmds->args[i])))
				return (error_invalid_symbols(cmds->args[i]));
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
