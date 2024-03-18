/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:27:13 by zmourid           #+#    #+#             */
/*   Updated: 2023/11/13 23:49:59 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	if (!s || !f)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, ft_strlen(s) + 1);
	i = 0;
	while (str[i])
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	return (str);
}
/*
char	upperIfModTwo(unsigned int i,char c)
{
	return (i%2 ? ft_tolower(c) : ft_toupper(c));
}
int	main(void)
{
	char	str[];
	char	*s;

	str[] = "hello world";
	s = ft_strmapi(str,upperIfModTwo);
	printf("the new = %s\n",s);
}
*/
