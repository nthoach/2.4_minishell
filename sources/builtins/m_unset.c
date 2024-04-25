/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:31:57 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/25 17:48:35 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../headers/minishell.h"

char	**whileloop_del_var(char **arr, char **rtn, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		if (!(ft_strncmp(arr[i], str, equal_sign(arr[i]) - 1) == 0
				&& equal_sign(arr[i]) == ft_strlen(str) + 1
				&& arr[i][ft_strlen(str)] == '='))
		{
			rtn[j] = ft_strdup(arr[i]);
			if (rtn[j] == NULL)
			{
				free_double_ptr((void **) rtn);
				return (rtn);
			}
			j++;
		}
		i++;
	}
	return (rtn);
}

char	**del_var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(i + 1, sizeof(char *));
	if (!rtn)
		return (NULL);
	rtn = whileloop_del_var(arr, rtn, str);
	return (rtn);
}

int	unset_error(t_cmds *cmds)
{
	if (invalid_identifier(cmds->args[1], 0))
	{
		ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
		ft_putstr_fd(cmds->args[1], STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (equal_sign(cmds->args[1]) != 0)
	{
		ft_putendl_fd("minishell: unset: not a valid identifier",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	m_unset(t_data *data, t_cmds *cmds)
{
	char	**tmp;

	if (!cmds->args[1])
		return (EXIT_SUCCESS);
	else if (unset_error(cmds) == 1)
		return (EXIT_FAILURE);
	else
	{
		tmp = del_var(data->envp, cmds->args[1]);
		free_double_ptr((void **) data->envp);
		data->envp = tmp;
	}
	return (EXIT_SUCCESS);
}
