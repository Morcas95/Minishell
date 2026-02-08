/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 00:52:24 by maalonso          #+#    #+#             */
/*   Updated: 2025/06/24 10:27:36 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

size_t			ft_printf(const char *format, ...);
int				ft_putchar(char c);
int				ft_putstr(char *str);
int				ft_putnbr(int n);
int				ft_putptr(void *ptr);
int				ft_puthex(unsigned long n);
int				ft_puthex_upper(unsigned long n);
unsigned int	ft_putunsigned(unsigned int n);

#endif
