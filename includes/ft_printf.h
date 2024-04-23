/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:24:00 by nthoach           #+#    #+#             */
/*   Updated: 2024/04/23 21:24:56 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef FT_PRINTF_Hß
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

int		ft_printf(const char *s, ...);
int		ft_putuint(unsigned int i);
int		ft_putnbr(int n);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_puthex_low(unsigned int nbr);
int		ft_puthex_up(unsigned int nbr);
int		ft_putpointer(unsigned long nbr);

#endif
