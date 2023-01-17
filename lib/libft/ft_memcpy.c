/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 21:59:21 by ede-smet          #+#    #+#             */
/*   Updated: 2022/05/21 19:07:25 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		k;
	char		*dstr;
	const char	*sstr;

	if (!dest && !src)
		return (NULL);
	dstr = (char *)dest;
	sstr = (char *)src;
	k = 0;
	while (k < n)
	{
		dstr[k] = sstr[k];
		k++;
	}
	return (dstr);
}
