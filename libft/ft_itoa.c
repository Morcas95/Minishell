/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:08:30 by maalonso          #+#    #+#             */
/*   Updated: 2025/04/23 12:01:46 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(int n)
{
	int	length;

	length = 1;
	while (n / 10)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	num;

	num = n;
	len = numlen(num);
	if (num < 0)
	{
		num = -num;
		len++;
	}
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (num % 10) + '0';
		num = num / 10;
		if (len == 0 && n < 0)
			str[len] = '-';
	}
	return (str);
}
