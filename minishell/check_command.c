/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongkseo <dongkseo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:01:22 by dongkseo          #+#    #+#             */
/*   Updated: 2023/05/13 00:57:38 by dongkseo         ###   ########.fr       */
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

int	check_whitespace(const char *command)
{
	int			i;

	i = 0;
	while (command[i])
	{
		if (command[i] != 32 && !(command[i] >= 9 && command[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}

// 더블쿼터와 = 변수가 처리가됩니다
// 싱글쿼터  = 변수처리가 되지않습니다

void	parse(const char *cmd, t_table *table, t_cmd_info **cmd_info)
{
	char	**result;
	char	**tmp;

	result = ft_split_quote(cmd, " ", table); // 쿼터 기준으로 스플릿합니다
	if (table->syntax_error)
		return ;
	tmp = ft_split_charset(cmd, " "); // 명령어를 | > >> 기준으로 스플릿합니다
	// 명령어 상태를 점검합니다 --> 만일 | > >> 뒤에 unexpect인자가 들어올 경우 syntax flag를 사용하여 에러처리 후 탈출합니다
	printf("charset : \n");
	for (int x = 0; tmp[x]; x++)
		printf("%s\n", tmp[x]);
	printf("\n\n\n\n");
	if (table->syntax_error)
	{
		printf("syntax error\n");
		exit(0);
	}
	for (int i = 0; result[i]; i++)
	{
		printf("%s\n", result[i]);
	}
	//check_operator(cmd, table);
	// 쿼터체크
	// 명령어 토근화
}



int	main(int ac, char *av[], char *env[])
{
	t_table		table;
	t_cmd_info	*cmd;
	char		*input_command;

	table.envp = copy_env(env);  // ---> 환경변수를 복사해둠으로써 팀원도 편하게 자원을 사용할 수 있도록 유도합니다
	while (ac && av)
	{
		input_command = readline("minishell$ "); // ---> 명령어 입력을 받도록합니다.
		if (!input_command)
			break ;
		if (*input_command != '\0' && !check_whitespace(input_command))
		{
			add_history(input_command); // 명령어를 기록하는 과정을 거칩니다 ----> history에 쌓이는 순사가 있을까요??
			parse(input_command, &table, &cmd);
			//table.exit_status = execute();
		}
		free(input_command);
	}
	ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
	ft_putstr_fd("\033[2D", STDOUT_FILENO);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	return (0);
}
