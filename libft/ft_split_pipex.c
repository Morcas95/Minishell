/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalonso <maalonso@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:08:19 by maalonso          #+#    #+#             */
/*   Updated: 2025/10/27 14:09:33 by maalonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_dots(const char *s, char c)
{
	size_t	i;
	size_t	sep;

	i = 0;
	sep = 0;
	while (s[i])
	{
		if (s[i] == c)
			sep++;
		i++;
	}
	return (sep + 1);
}

static int	fill_tokens(char **str, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (1)
	{
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i == start)
			str[j++] = NULL;
		else
		{
			str[j] = const_ft_substr(s, start, i - start);
			if (!str[j++])
				return (0);
		}
		if (!s[i])
			break ;
		i++;
	}
	str[j] = NULL;
	return (1);
}

char	**ft_split_pipex(char const *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (count_dots(s, c) + 1));
	if (!str)
		return (NULL);
	if (!fill_tokens(str, s, c))
		return (NULL);
	return (str);
}
