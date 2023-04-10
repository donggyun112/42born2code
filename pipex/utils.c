/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 03:28:03 by dongkseo          #+#    #+#             */
/*   Updated: 2023/04/11 03:46:24 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

void	free_all(char **str, char *tmp)
{
	int	i;

	i = 0;
	free(tmp);
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	error_flag(char *error_messege, int *flag)
{
	perror(error_messege);
	*flag = 1;
}

void	exit_error(const char *error, int errorcode, int error_status)
{
	if (error_status == EXIT_FAILURE)
		perror(error);
	else
		ft_putendl_fd(error, STDERR_FILENO);
	exit(errorcode);
}

void	push_cmd(t_cmd **node, char *cmd)
{
	t_cmd	*tmp;
	t_cmd	*head;

	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	if (!tmp)
		exit_error("allocate fail", -1, EXIT_FAILURE);
	tmp->cmd = cmd;
	tmp->next = NULL;
	if (!*node)
		*node = tmp;
	else
	{
		head = *node;
		while (head->next)
			head = head->next;
		head->next = tmp;
	}
}
