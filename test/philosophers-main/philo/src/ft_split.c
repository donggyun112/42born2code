/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongmpa <seongmpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:41:30 by seongmpa          #+#    #+#             */
/*   Updated: 2023/03/30 17:41:42 by seongmpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static size_t	check_size(char *s, char c)
{
	size_t	size;

	size = 0;
	while (*s)
	{
		if (*s != c)
			size++;
		while (*s != c)
		{
			s++;
			if (*s == '\0')
				return (size);
		}
		s++;
	}
	return (size);
}

static char	**free_all(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static char	*ft_strndup(char *s1, size_t n)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (dest == 0)
		return (0);
	while (i < n)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**make_result(char **result, char *s, char c, size_t result_size)
{
	size_t	word_idx;
	size_t	word_size;

	word_idx = 0;
	while (word_idx < result_size)
	{
		word_size = 0;
		while (*s == c && *s != '\0')
			s++;
		while (*s != c && *s != '\0')
		{
			word_size++;
			s++;
		}
		s -= word_size;
		result[word_idx] = ft_strndup(s, word_size);
		if (!result[word_idx])
		{
			free_all(result);
			return (NULL);
		}
		s += word_size;
		word_idx++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	result_size;

	if (!s)
		return (NULL);
	result_size = check_size((char *)s, c);
	result = (char **)malloc(sizeof(char *) * (result_size + 1));
	if (!result)
		return (0);
	result[result_size] = NULL;
	result = make_result(result, (char *)s, c, result_size);
	return (result);
}
