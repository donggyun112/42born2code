/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:21:19 by dongkseo          #+#    #+#             */
/*   Updated: 2023/05/09 02:19:21 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*arr;
	size_t	i;
	size_t	slen;
	size_t	sublen;

	if (!s)
		return (NULL);
	slen = ft_strlen((char *)s);
	if (slen <= start)
	{
		arr = (char *)malloc(1);
		*arr = '\0';
		return (arr);
	}
	sublen = slen - start;
	if (sublen > len)
		sublen = len;
	arr = (char *)malloc(sublen + 1);
	if (!arr)
		return (NULL);
	i = -1;
	while (s[start + (++i)] && i < sublen)
		arr[i] = s[start + i];
	arr[i] = '\0';
	return (arr);
}

char	*ft_strjoin(const char *s1, char const *s2)
{
	size_t		len1;
	size_t		len2;
	char		*buf;

	len1 = 0;
	len2 = 0;
	buf = NULL;
	if (!s2)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	buf = (char *)malloc(len1 + len2 + 1);
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	if (s1 != NULL)
		ft_strcat(buf, s1);
	if (s2 != NULL)
		ft_strcat(buf, s2);
	return (buf);
}

char	*ft_strcat(char *string1, const char *string2)
{
	int	i;

	i = 0;
	while (string1[i])
		i++;
	while (*string2)
	{
		string1[i] = *string2;
		string2++;
		i++;
	}
	string1[i] = '\0';
	return (string1);
}

char	*ft_strchr(const char *string, int c)
{
	while (*string != (char)c)
	{
		if (*string == '\0')
			return (0);
		string++;
	}
	return ((char *)string + 1);
}
