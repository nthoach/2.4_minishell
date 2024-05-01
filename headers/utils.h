/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:25:22 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/25 17:32:46 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef data_H
# define data_H
# include "parsing.h"
# include "minishell.h"

// data
int		ini2_data(t_data *data);
char	**ft_arrdup(char **arr);

void	free1_data(t_data *data);
void	ini1_data(t_data *data, char **envp);

#endif
