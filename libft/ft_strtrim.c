/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:45:14 by zmourid           #+#    #+#             */
/*   Updated: 2023/11/18 01:05:25 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	s_len;

	if (!s1)
		return (NULL);
	if (!set || !*set)
		return (ft_strdup(s1));
	s_len = ft_strlen(s1);
	end = s_len;
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if (start == s_len)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[end - 1]))
		end--;
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 1);
	return ((char *)str);
}
