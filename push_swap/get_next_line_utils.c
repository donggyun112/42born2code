/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:20:34 by dongkseo          #+#    #+#             */
/*   Updated: 2023/03/20 12:21:13 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*buf;

	len1 = 0;
	len2 = 0;
	if (s1 != NULL)
		len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	buf = (char *)malloc(len1 + len2 + 1);
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	if (s1 != NULL)
		ft_strcat(buf, s1);
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
	return ((char *)string);
}
