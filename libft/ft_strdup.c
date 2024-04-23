/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:28:36 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/23 21:28:38 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str_d;
	int		size;
	int		i;

	size = ft_strlen((char *)s);
	str_d = (char *)malloc((size + 1) * sizeof(char));
	if (!str_d)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str_d[i] = (char)s[i];
		i++;
	}
	str_d[i] = '\0';
	return (str_d);
}
