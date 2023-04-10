#include <unistd.h>

int main(int ac, char **av)
{
	if (ac != 3)
	{
		write(1, "\n" , 1);
		return (0);
	}
	char *str1 = av[1];
	char *str2 = av[2];
	int dat[200] = { 0 };
	int i = 0;
	while (str1[i])
	{
		dat[(int)str1[i]]++;
		i++;
	}
	i = 0;
	while (str2[i])
	{
		dat[(int)str2[i]]++;
		i++;
	}
	i = 0;
	while (str1[i])
	{
		write(1, &str1[i], 1);
		dat[(int)str1[i]] = 0;
		i++;
	}
	i = 0;
	while (str2[i])
	{
		if (dat[(int)str2[i]] >= 1)
		{
			write(1, &str2[i], 1);
			dat[(int)str2[i]] = 0;
		}
		i++;
	}
	write(1, "\n" , 1);
}