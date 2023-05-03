#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
void	loopfunc(int num)
{
	int tmp = 0;
	for (int i = 0; i < num; i++)
		tmp += 1;
}

float timediff(struct timeval start, struct timeval end)
{
	return (end.tv_sec - start.tv_sec + 1e-6 * (end.tv_usec - start.tv_usec));
}

int main()
{
	struct timeval start;
	struct timeval end;

	gettimeofday(&start, NULL);
	loopfunc(10000);
	gettimeofday(&end, NULL);
	printf("%f", timediff(start, end));
	return (0);
}