/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:07:54 by honguyen          #+#    #+#             */
/*   Updated: 2024/05/13 17:19:55 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	if (!ft_strncmp(s1, s2, ft_strlen(s2))
		&& !ft_strncmp(s1, s2, ft_strlen(s1)))
		return (0);
	return (1);
}
