/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 12:22:56 by ede-smet          #+#    #+#             */
/*   Updated: 2023/01/11 12:26:51 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digit(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*itoa_pos(char *s, int n)
{
	int	i;

	i = ft_count_digit(n);
	s[i--] = '\0';
	while (i >= 0)
	{
		s[i--] = n % 10 + '0';
		n = n / 10;
	}
	return (s);
}

static char	*itoa_neg(char *s, int n)
{
	int			i;
	int long	nb;

	nb = n;
	nb *= -1;
	i = ft_count_digit(nb);
	s[i + 1] = '\0';
	s[0] = '-';
	while (i > 0)
	{
		s[i--] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char	*str;

	str = NULL;
	if (n < 0)
		str = malloc(sizeof(char) * (ft_count_digit(n) + 2));
	else if (n > 0)
		str = malloc(sizeof(char) * (ft_count_digit(n) + 1));
	else
		str = malloc(sizeof(char) + 1);
	if (!str)
		return (NULL);
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (n < 0)
		str = itoa_neg(str, n);
	else
		str = itoa_pos(str, n);
	return (str);
}
