/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:15:20 by zmourid           #+#    #+#             */
/*   Updated: 2023/11/07 16:58:41 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	get_size(long n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n / 10)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	long	nbr;
	int		is_negative;
	char	*res;

	is_negative = 0;
	nbr = n;
	len = get_size(nbr);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	res[len--] = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		is_negative = 1;
		res[0] = '-';
	}
	while (len >= is_negative)
	{
		res[len--] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (res);
}
