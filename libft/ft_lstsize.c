/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:27:36 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/23 21:27:39 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"
//#include <stdio.h>

int	ft_lstsize(t_list *lst)
{
	int	n;

	if (!lst)
		return (0);
	n = 0;
	while (lst)
	{
		lst = lst->next;
		n++;
	}
	return (n);
}

// int	main()
// {
// 	t_list *lst[1] = {ft_lstnew("akakaka")};
// 	t_list *new;
// 	new = ft_lstnew("sdds");
// 	ft_lstadd_front(lst, new);
// 	new = ft_lstnew("sddsh");
// 	ft_lstadd_front(lst, new);
// 	printf("\n\n > lst %d\n",ft_lstsize(new));
// 	return (0);
// }