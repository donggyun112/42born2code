/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:45:26 by dongkseo          #+#    #+#             */
/*   Updated: 2023/03/20 11:45:26 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

//utils
char	*ft_strjojo(const char *s1, char const *s2);
char	*ft_strcat_v2(char *string1, const char *string2);
//main
char	*ft_strdup_v2(const char *string, int *start, int *flag);
char	*ft_processing(int fd, int *start, int *flag, char **stack);
char	*get_next_line(int fd);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2561
# endif

#endif
