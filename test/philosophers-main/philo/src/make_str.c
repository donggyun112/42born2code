/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongmpa <seongmpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:40:58 by seongmpa          #+#    #+#             */
/*   Updated: 2023/03/30 17:51:57 by seongmpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static char	*ft_strncat(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s2[i])
	{
		s1[i + n] = s2[i];
		i++;
	}
	return (s1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*result;
	size_t			len1;
	size_t			len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (0);
	result = ft_strncat(result, (char *)s1, 0);
	result = ft_strncat(result, (char *)s2, len1);
	result[len1 + len2] = 0;
	return (result);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (dest == 0)
		return (0);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	check_size_double_array(char **str)
{
	int	size;

	size = -1;
	while (str[++size])
		;
	return (size);
}

char	**make_str(char **argv)
{
	int		size;
	char	*str;
	char	*tmp;
	char	**res;
	int		i;

	i = 0;
	size = check_size_double_array(argv);
	str = ft_strdup(argv[0]);
	while (++i < size - 1)
	{
		tmp = ft_strjoin(str, " ");
		free(str);
		str = ft_strjoin(tmp, argv[i]);
		free(tmp);
	}
	tmp = ft_strjoin(str, " ");
	free(str);
	str = ft_strjoin(tmp, argv[i]);
	free(tmp);
	res = ft_split(str, ' ');
	free(str);
	return (res);
}
