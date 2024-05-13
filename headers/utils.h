/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:00:24 by honguyen          #+#    #+#             */
/*   Updated: 2024/05/13 17:01:22 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "parsing.h"
# include "minishell.h"

int		ini2_data(t_data *data);
char	**ft_arrdup(char **arr);
void	free1_data(t_data *data);
void	ini1_data(t_data *data, char **envp);
#endif
