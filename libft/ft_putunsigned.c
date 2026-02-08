/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:33:55 by maalonso          #+#    #+#             */
/*   Updated: 2025/05/05 12:58:52 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_putunsigned(unsigned int n)
{
	int		count;

	count = 0;
	if (n >= 10)
		count += ft_putunsigned(n / 10);
	count += ft_putchar((n % 10) + '0');
	return (count);
}
