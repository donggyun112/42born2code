/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:33:32 by dongkseo          #+#    #+#             */
/*   Updated: 2023/05/09 02:19:22 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	make_str(int fd, t_tools *t, t_tmp *d)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || t->rd < 0)
		return (1);
	t->rd = read(fd, d->buff, BUFFER_SIZE);
	if (t->rd < 0)
	{
		t->rd = 0;
		free(t->backup);
		t->backup = NULL;
		return (1);
	}
	d->buff[t->rd] = '\0';
	d->tmp1 = ft_strjoin(t->backup, d->buff);
	d->tmp2 = ft_strchr(d->tmp1, '\n');
	free(t->backup);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_tools	t;
	t_tmp			d;

	if (make_str(fd, &t, &d))
		return (NULL);
	if (!d.tmp2)
		t.backup = d.tmp1;
	else
	{
		d.tmp3 = ft_substr(d.tmp1, 0, d.tmp2 - d.tmp1);
		t.backup = ft_substr(d.tmp2, 0, ft_strlen(d.tmp2));
		free(d.tmp1);
		return (d.tmp3);
	}
	if (t.rd > 0)
		return (get_next_line(fd));
	d.tmp2 = ft_substr(d.tmp1, 0, ft_strlen(d.tmp1));
	free(t.backup);
	t.backup = NULL;
	if (!*(d).tmp2)
	{
		free(d.tmp2);
		return (NULL);
	}
	return (d.tmp2);
}

/* int main()
{
	char *line;
	int fd;
	fd = open("read_error.txt", O_RDONLY);
	line = get_next_line(fd);
	printf ("%s", line);
	free(line);
	line = get_next_line(fd);
	printf ("%s", line);
	free(line);
	line = get_next_line(fd);
	printf ("%s", line);
	free(line);
} */