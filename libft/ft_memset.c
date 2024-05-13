/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:16:54 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/13 17:20:47 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *by, int c, size_t size)
{
	unsigned char	*p;

	p = (unsigned char *) by;
	while (size--)
		*p++ = (unsigned char) c;
	return (by);
}
