/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:14:15 by maalonso          #+#    #+#             */
/*   Updated: 2025/04/10 12:14:17 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!src && !dest)
		return (0);
	if (dest >= src)
	{
		while (n > 0)
		{
			n--;
			((char *)dest)[n] = ((const char *)src)[n];
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
