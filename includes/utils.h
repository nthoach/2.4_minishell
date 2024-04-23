/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:25:22 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/23 21:25:24 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef UTILS_H
# define UTILS_H
# include "parsing.h"
# include "minishell.h"

// utils
int		implement_utils(t_utils *utils);
char	**ft_arrdup(char **arr);

void	free_utils(t_utils *utils);
void	init_utils(t_utils *utils, char **envp);

#endif
