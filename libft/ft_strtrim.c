/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:20:50 by maalonso          #+#    #+#             */
/*   Updated: 2025/04/23 11:57:40 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	inicio;
	size_t	fin;
	char	*str;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	inicio = 0;
	fin = ft_strlen(s1);
	while (s1[inicio] && ft_strchr(set, s1[inicio]))
		inicio++;
	while (fin > inicio && ft_strchr(set, s1[fin - 1]))
		fin--;
	str = (char *)malloc(fin - inicio + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (inicio < fin)
	{
		str[i] = s1[inicio];
		inicio++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
