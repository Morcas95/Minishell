/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:54:36 by maalonso          #+#    #+#             */
/*   Updated: 2025/04/10 15:54:38 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_c;

	last_c = 0;
	while (*s)
	{
		if (*s == (char)c)
			last_c = s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)last_c);
}
