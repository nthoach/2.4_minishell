/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:26:00 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/13 17:57:36 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num_elem, size_t size)
{
	unsigned char	*array;

	array = (unsigned char *)malloc(num_elem * size);
	if (array == NULL)
		return (NULL);
	ft_bzero(array, num_elem * size);
	return ((void *)array);
}
