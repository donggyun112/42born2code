#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int	fd;
	int	ret;

	fd = open("test.txt",  O_TRUNC | O_CREAT | O_RDWR);
	dup2(fd, STDOUT_FILENO);
	//ret = fd
	ret = dup2(STDERR_FILENO, fd);
	write(STDERR_FILENO, "???", 3);
	printf("qweqwe");

	return (0);
}