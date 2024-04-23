/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:27:01 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/23 21:27:03 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst && f)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// int main()
// {
// 	t_list *lst = {ft_lstnew("akakaka")};
// 	t_list *new;
// 	void *del;
// 	del = '\0';
// 	char str[] = "oif";		
// 	new = ft_lstnew(&str);
// 	printf("\n\n > the content of lst %s\n", (char *)lst->content);
// 	printf(" > the content of next %s\n",(char *) new->content);
// 	ft_lstadd_back(&lst, new);
// 	ft_lstiter(lst, del);
// 	printf(" > the content of lst %s\n", (char *)lst->content);
// 	printf(" > the content of next %s\n", (char *) lst->next->content);
// }
