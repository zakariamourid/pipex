/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:19:54 by zmourid           #+#    #+#             */
/*   Updated: 2023/11/10 20:22:45 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	if ((dst == src) || !len)
		return (dst);
	if (d > s)
	{
		while (len > i)
		{
			d[len - 1 - i] = s[len - 1 - i];
			i++;
		}
	}
	else
	{
		while (len--)
			*d++ = *s++;
	}
	return (dst);
}
