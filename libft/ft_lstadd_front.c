/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:26:24 by nthoach           #+#    #+#             */
/*   Updated: 2024/05/13 17:02:55 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new && lst)
	{
		new->next = *lst;
		*lst = new;
	}
}

// int main()
// {
// 	t_list *lst[1] = {ft_lstnew("akakaka")};
// 	t_list *new;
// 	new = ft_lstnew("sdds");
// 	ft_lstadd_front(lst, new);
// 	printf("\n> lst %s\n", (char *)new->content);
// 	printf("\n> lst %p\n", new->next);
// 	printf("\n> lst %s\n", (char *)new->next->content);
// 	printf("\n> lst %p\n", *lst);
// }
