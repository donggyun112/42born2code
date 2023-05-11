/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:03:00 by dongkseo          #+#    #+#             */
/*   Updated: 2023/05/11 19:13:12 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	is_exist(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_strmylen(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] && is_exist(str[i], charset))
		i++;
	return (i);
}

char	**ft_clearall(int j, char **arr)
{
	while (j > 0)
		free(arr[--j]);
	free(arr);
	return (NULL);
}

void	make_new_malloc(char *str, char *charset, char **arr)
{
	int	len;
	int	i;
	int	j;

	j = 0;
	while (*str)
	{
		if (is_exist(*str, charset))
		{
			len = ft_strmylen(str, charset);
			arr[j] = (char *)malloc(len + 1);
			if (!arr[j])
				return (ft_clearall(j, arr))
			i = 0;
			while (*str && (is_exist(*str, charset)))
				arr[j][i++] = *str++;
			arr[j][i] = '\0';
			j++;
		}
		else
			str++;
	}
}

char	**ft_split(char *str, char *charset)
{
	int		i;
	int		word;
	char	**arr;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (is_exist(str[i], charset))
		{
			word++;
			while ((is_exist(str[i], charset)) && str[i])
				i++;
		}
		else
			i++;
	}
	arr = (char **)malloc(sizeof(char *) * (word + 1));
	arr[word] = NULL;
	make_new_malloc(str, charset, arr);
	return (arr);
}