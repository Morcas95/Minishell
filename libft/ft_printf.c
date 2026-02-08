/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 00:47:52 by maalonso          #+#    #+#             */
/*   Updated: 2025/05/05 14:10:25 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	format(const char type, va_list args)
{
	size_t	count;

	count = 0;
	if (type == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (type == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (type == 'd' || type == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (type == 'u')
		count += ft_putunsigned(va_arg(args, unsigned int));
	else if (type == 'p')
		count += ft_putptr(va_arg(args, void *));
	else if (type == 'x')
		count += ft_puthex(va_arg(args, unsigned int));
	else if (type == 'X')
		count += ft_puthex_upper(va_arg(args, unsigned int));
	else if (type == '%')
		count += ft_putchar('%');
	return (count);
}

size_t	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	count;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			count += format(*str, args);
		}
		else
			count += ft_putchar(*str);
		str++;
	}
	va_end(args);
	return (count);
}
