/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:07:33 by ede-smet          #+#    #+#             */
/*   Updated: 2022/04/12 16:07:33 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	int		j;

	j = 0;
	i = 0;
	if (ft_strlen((char *)little) == 0)
		return ((char *)big);
	while (j != (int)ft_strlen((char *)little) && big[i] && i < len)
	{
		i = i - j;
		j = 0;
		while (big[i] && big[i] == little[j] && i < len)
		{
			i++;
			j++;
		}
		i++;
	}
	if (j == (int)ft_strlen((char *)little))
		return ((char *)big + (i - j - 1));
	return (NULL);
}
