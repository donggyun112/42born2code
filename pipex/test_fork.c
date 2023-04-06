#include "Libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int	fd[2];
	int	status;
	pid_t pid;

	char	buf[30];
	if (status == -1)
	{
		printf("error");
		exit(-1);
	}	
	pid = fork();
	if (pid == 0) // 자식 프로세스
	{
		wait(&status);
		for (int x = 0; x < 10; x++)
		{
			printf("i'm child%d\n", x + 1);
			sleep(1);
		}
	}
	else
	{
		printf("i wait child\n");
		wait(&status);
		printf("\nchild exit");
	}
	
	return (0);
}