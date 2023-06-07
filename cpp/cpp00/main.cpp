#include <iostream>
#include <string>
#include <cstring>

int main(int ac, char **av)
{
	for (int i = 1; i < ac; i++)
	{
		std :: cout << av[i];
		if (i < ac - 1)
			std :: cout << " ";
	}
	std :: cout << std :: endl;
	return (0);
}