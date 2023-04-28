/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:09:20 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/22 00:54:08 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, size_t color)
{
	char	*dst;

	if (1095 < x || 795 < y || x < 0 || y < 0)
		return ;
	dst = data->addr + ((y * data->bit_sizeline) + (x * (data->bit_pixel / 8)));
	if (*(unsigned int *)dst != 0x000000)
		return ;
	*(unsigned int *)dst = color;
}

void	push(t_map_data **map, float x, float z, size_t color)
{
	t_map_data	*tmp;

	tmp = *map;
	if (tmp == NULL)
	{
		*map = (t_map_data *)malloc(sizeof(t_map_data));
		(*map)->x = x;
		(*map)->z = z;
		(*map)->color = color;
		(*map)->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_map_data *)malloc(sizeof(t_map_data));
		tmp->next->x = x;
		tmp->next->z = z;
		tmp->color = color;
		tmp->next->next = NULL;
	}
}

int	map_size(char **av)
{
	int		fd;
	char	*line;
	int		size;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	size = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		size++;
	}
	close(fd);
	return (size);
}

int	image_size_(int flag, char **av, t_image *image)
{
	if (flag == 0)
		return (map_size(av) - 1);
	else
		return (image->size / 50);
}

void	array_clear(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	tmp = NULL;
}
