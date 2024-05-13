/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:31:02 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/13 17:21:09 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	(*builtin_arr(char *str))(t_data *data, t_cmds *cmds)
{
	static void	*builtins[7][2] = {{"echo", m_echo}, {"cd", m_cd}, {"pwd",
		m_pwd}, {"export", m_export}, {"unset", m_unset}, {"env", m_env},
	{"exit", m_exit}};
	int			i;

	i = 0;
	while (str && i < 7)
	{
		if (!ft_strncmp(builtins[i][0], str, ft_strlen((builtins[i][0])))
			&& !ft_strncmp(builtins[i][0], str, ft_strlen(str)))
			return (builtins[i][1]);
		i++;
	}
	return (NULL);
}

int	p_specific_path(t_data *data, char *str)
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
	return (ret);
}
