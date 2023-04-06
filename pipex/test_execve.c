#include "pipex.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "Libft/libft.h"

// access(filepath, mod) --> 파일의 권한을 확인합니다 성공시 0 실패시 -1
// execv file path들어오면 (절대경로) 내부명령어
// perror 에러 메세지 출력을 위한 함수
// strerror errno변수를 에러 코드를 반환 받은 후 에러 코드에 맞게 에러 출력
// dup, dup2 ??? 잘 모르겠음
// execve 첫번째 인자는 파일경로 두번째 인자는 명령어 세번째 인자는 환경변수가 들어간다?
// fork

void	error_print()
{
	perror(strerror(errno));
	errno = 0;
}

int	ft_strcmp(const char *s1, const char *s2)
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

int main(int ac, char **av, char **env)
{
	char *str[2];
	str[1] = NULL;
	int z = 3;
	char **split_tmp;
	int i = 0;
	while (*env)
	{
		if (ft_strncmp(*env, "PATH", 4) == 0)
		{
			split_tmp = ft_split(*env, ':');
			split_tmp[0] = split_tmp[0] + 5;
			while (split_tmp[i])
			{
				str[0] = ft_strjoin(split_tmp[i], "/ls");
				z = access(str[0], X_OK);
				i++;
			}
		}
		env++;
	}
}
