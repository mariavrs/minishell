/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:13:50 by ede-smet          #+#    #+#             */
/*   Updated: 2022/05/21 19:17:22 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				k;
	unsigned char		*dstr;
	unsigned char		*sstr;

	if (!dest && !src)
		return (NULL);
	dstr = (unsigned char *)dest;
	sstr = (unsigned char *)src;
	k = 0;
	if (!dest && !src)
		return (NULL);
	if (sstr < dstr)
	{
		while (++k <= n)
			*(dstr + n - k) = *(sstr + n - k);
	}
	else
	{
		while (n-- > 0)
		{
			*(dstr + k) = *(sstr + k);
			k++;
		}
	}
	return (dstr);
}
