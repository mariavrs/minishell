/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:29:59 by ede-smet          #+#    #+#             */
/*   Updated: 2023/03/19 15:14:52 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	s_size;
	size_t	i;

	i = -1;
	sub_s = NULL;
	s_size = ft_strlen((char *)s);
	if (start < s_size)
	{
		if (len < s_size - start)
			sub_s = malloc((len + 1) * sizeof(char));
		else
			sub_s = malloc((s_size - start + 1) * sizeof(char));
		if (!sub_s)
			return (NULL);
		while (s[++i + start] && i < len)
			sub_s[i] = s[i + start];
	}
	else
	{
		sub_s = malloc(sizeof(char));
		if (!sub_s)
			return (NULL);
	}
	return (sub_s[i] = '\0', sub_s);
}
