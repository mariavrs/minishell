/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:22:34 by ede-smet          #+#    #+#             */
/*   Updated: 2023/01/11 12:41:12 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_c(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	wrd;

	wrd = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			wrd++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (wrd);
}

static char	**ft_fill_strings(char const *s, char c, char **split)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	j = 0;
	while (s[i] && j < ft_count_words(s, c))
	{
		k = 0;
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			split[j] = malloc((ft_count_c(&s[i], c) + 1) * sizeof(char));
			if (!split[j])
				return (NULL);
		}
		while (s[i] && s[i] != c)
			split[j][k++] = s[i++];
		split[j++][k] = '\0';
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (s == NULL)
		return (NULL);
	split = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split[ft_count_words(s, c)] = NULL;
	if (ft_count_words(s, c) != 0)
		return (ft_fill_strings(s, c, split));
	else
		split[0] = NULL;
	return (split);
}
