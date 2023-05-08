/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:44:35 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/11 22:10:44 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_v2(const char *string, int *start, int *flag)
{
	int		len;
	int		i;
	char	*arr;

	len = ft_strlen((char *)string);
	arr = (char *)malloc(len + 1);
	if (!arr)
		return (NULL);
	i = 0;
	while (string[i] && string[i] != '\n')
	{
		arr[i] = string[i];
		i++;
		*start += 1;
	}
	if (string[i] == '\0')
		*flag = 1;
	if (string[i] == '\n')
	{
		arr[i] = string[i];
		*start += 1;
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	*ft_processing(int fd, int *start, int *flag, char **stack)
{
	char	buff[BUFFER_SIZE + 1];
	int		rd_size;
	char	*temp;

	rd_size = 1;
	while (rd_size)
	{
		rd_size = read(fd, buff, BUFFER_SIZE);
		if (!rd_size)
			break ;
		if (rd_size < 0)
			return (NULL);
		buff[rd_size] = '\0';
		temp = ft_strjoin(*stack, buff);
		if (temp)
		{
			free(*stack);
			*stack = temp;
		}
		else
			return (NULL);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (ft_strdup_v2(*stack + *start, &(*start), &(*flag)));
}

int	check_val(char **temp, int flag, char **stack, int *start)
{
	if (*temp == NULL || flag == 1)
	{
		free(*stack);
		*start = 0;
		*stack = NULL;
	}
	if (*temp != NULL && !**temp)
	{
		free(*temp);
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*temp;
	static int	start;
	static char	*stack;
	int			flag;

	temp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stack == NULL)
	{
		stack = malloc(sizeof(char) * 1);
		*stack = '\0';
	}
	flag = 0;
	temp = ft_processing(fd, &start, &flag, &stack);
	if (check_val(&temp, flag, &stack, &start))
		return (NULL);
	return (temp);
}
