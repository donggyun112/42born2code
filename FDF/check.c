/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 21:24:25 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/21 22:41:44 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_line(t_image *image, int x)
{
	if (image->line_n != 0 && image->line_n != x)
		ft_error("line Error");
	image->line_n = x;
	return (0);
}

int	is_valid_file_type(char *file_path)
{
	char	**path;
	int		answer;
	int		i;

	answer = 0;
	i = 0;
	path = ft_split(file_path, '.');
	if (!path)
		error_("split error");
	while (path[i] != 0)
		i++;
	if (ft_strncmp(path[i - 1], "fdf", 4) == 0)
		answer = 1;
	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	return (answer);
}
