/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 23:18:30 by zmourid           #+#    #+#             */
/*   Updated: 2023/11/18 01:04:12 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
			{
				i++;
			}
		}
		else
		{
			i++;
		}
	}
	return (count);
}

static int	word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static void	free_array(char **str, int len)
{
	while (len--)
		free(str[len]);
	free(str);
}

static char	**ft_split2(char const *s, char **str, int word, char c)
{
	int	i;

	i = 0;
	while (word < count_words(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		str[word] = ft_substr(s, i, word_len(&s[i], c));
		if (!str[word])
		{
			free_array(str, word);
			return (NULL);
		}
		while (s[i] != c && s[i])
			i++;
		word++;
	}
	str[word] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		word;
	char	**str;

	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!str)
		return (NULL);
	word = 0;
	str = ft_split2(s, str, word, c);
	return (str);
}
