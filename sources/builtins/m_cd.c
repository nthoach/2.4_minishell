/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:31:09 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/25 17:48:28 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../headers/minishell.h"
// find the string str in envp and return its remain part of envp[i] excluding str
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

// using this function I compare the path passed
// by user with my environmental variable and save it in temp
// and using chdir inbuilt function I change path
// will return 0 if it successfully changes the working directory
// if it didn't successfully change the directory
// it will go inside the if condition to print error
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

/*
updates the PWD and OLDPWD environment variables
// searching for PWD= in the envp double array
and returns 0 when it finds it by comparing first 4 characters
// It will concatinate the new working directory
with PWD= and update it in the env variable (PWD=/users/szerisen)
// This will do the same thing as the first one
which is concatinating OLDPWD= with the value of old_pwd
*/
void	update_path_to_env(t_data *data)
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

// if str[1] is empty the (i.e if the user passes cd
// without any option then this redirects him to home directory)
// checking if the first argument (cmds->args[1]) starts with a
// hyphen ("-"). This means the user wants to go to previous directory.
// printing the string "minishell: " to the standard error file
// descriptor (incase there is an error while executing cd command)
// this line is used to print the value of
// cmds->args[1] to the standard error stream.
// checks if the return value is not equal to 0. A return value
// of 0 typically indicates a successful execution of chdir.
// This function will update the pwd and old_pwd variables
// with the new paths.
int	cd_helper(t_data *data, t_cmds *cmds)
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

int	m_cd(t_data *data, t_cmds *cmds)
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
	change_path(data);
	update_path_to_env(data);
	return (EXIT_SUCCESS);
}
