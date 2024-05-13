/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:57:36 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/13 17:20:46 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *d, const void *s, size_t len)
{
	const unsigned char	*src;
	unsigned char		*dst;

	src = (const unsigned char *) s;
	dst = (unsigned char *) d;
	if ((dst > src) && (dst < src + len))
	{
		src += len - 1;
		dst += len - 1;
		while (len--)
			*dst-- = *src--;
		return (d);
	}
	else
		return (ft_memcpy(d, s, len));
}
