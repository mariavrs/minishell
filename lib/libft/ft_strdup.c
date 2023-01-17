/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:17:14 by ede-smet          #+#    #+#             */
/*   Updated: 2022/05/08 11:08:04 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s_cp;
	int		i;

	i = -1;
	s_cp = NULL;
	s_cp = malloc(ft_strlen((char *)s) * sizeof(char) + 1);
	if (!s_cp)
		return (NULL);
	while (s[++i])
		s_cp[i] = s[i];
	s_cp[i] = '\0';
	return (s_cp);
}
