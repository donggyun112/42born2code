/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 03:27:43 by dongkseo          #+#    #+#             */
/*   Updated: 2023/06/27 18:22:11 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

void	init_here_doc_data(t_av *t, char *limits, char **av)
{
	int		fd;
	char	*line;

	fd = open("/tmp/sh-thd-1641928925", \
	O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	t->infile = dup(fd);
	t->tmp = ft_strjoin(limits, "\n");
	while (1)
	{
		line = get_next_line(0);
		if (!line || ft_strcmp(line, t->tmp) == 0)
			break ;
		write(t->infile, line, ft_strlen(line));
		free(line);
	}
	free(t->tmp);
	close(t->infile);
	t->infile = open("/tmp/sh-thd-1641928925", O_RDONLY);
	close(fd);
	unlink("/tmp/sh-thd-1641928925");
	t->outfile = open(av[t->ac - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (t->outfile == -1)
		exit_error("Error outfile", 1, EXIT_FAILURE);
}

void	ft_here_doc_processing(char **av, char **env, int ac)
{
	t_av	t;
	t_cmd	*node;
	char	*path;

	t.ac = ac;
	t.flag = BONUS;
	init_here_doc_data(&t, av[2], av);
	path = get_path(env);
	node = ft_processing_cmd(path, av, t);
	parse_cmd(node, av, t);
	run_proccess(t, env, node);
	exit(0);
}
