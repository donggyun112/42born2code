/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:01:22 by dongkseo          #+#    #+#             */
/*   Updated: 2023/05/11 19:13:06 by dongkseo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 전역변수는 시그널을 전역변수로 두어야합니다.

char	**copy_env(char **env)
{
	char	**tmp;
	int		i;

	i = 0;
	while (env[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * i);
	if (!tmp)
		return (NULL);
	i = -1;
	while (env[++i])
		tmp[i] = ft_strdup(env[i]);
	tmp[i] = NULL;
	return (tmp);
}

// 더블쿼터와 = 변수가 처리가됩니다
// 싱글쿼터  = 변수처리가 되지않습니다

int	main(int ac, char **av, char **env)
{
	t_table	table;
	char	*input_command;

	(void)ac;
	(void)av;
	table.envp = copy_env(env);  // ---> 환경변수를 복사해둠으로써 팀원도 편하게 자원을 사용할 수 있도록 유도합니다
	while (true)
	{
		input_command = readline("minishell$ "); // ---> 명령어 입력을 받도록합니다.
		if (!input_command)
			break ;
		if (*input_command != '\0')
		{
			// 명령어를 파씽합니다
			// 명령어를 실행합니다
			// 명령어를 free해줍니다
		}
	}
	ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
	ft_putstr_fd("\033[2D", STDOUT_FILENO);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	return (0);
}
