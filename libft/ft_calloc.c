/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:10:59 by zmourid           #+#    #+#             */
/*   Updated: 2023/11/18 00:47:40 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*data;

	if (size != 0 && count > (SIZE_MAX / size))
		return (NULL);
	data = malloc(count * size);
	if (!data)
		return (NULL);
	ft_bzero(data, count * size);
	return (data);
}
