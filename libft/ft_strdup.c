/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:03:56 by maalonso          #+#    #+#             */
/*   Updated: 2025/04/14 14:03:57 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*ptr;

	ptr = (char *)malloc(ft_strlen(s) + 1);
	if (!ptr)
		return (0);
	ft_memmove(ptr, s, ft_strlen(s));
	ptr[ft_strlen(s)] = '\0';
	return (ptr);
}
