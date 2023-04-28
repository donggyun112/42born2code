#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct base
{
	int w;
	int h;
	char *arr;
} base;

typedef struct data
{
	char type;
	float x;
	float y;
	float w;
	float h;
	char shape;
} data;

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	get_info(base *base, FILE *file)
{
	char *tmp;
	char shape;
	int ret;

	ret = fscanf(file, "%d %d %c\n", &base->w, &base->h, &shape);
	if (ret == 3)
	{
		if ((base->w < 1 || base->h < 1) || (base->w > 300 || base->h > 300))
			return (1);
		tmp = malloc(base->w * base->h);
		base->arr = tmp;
		if (!base->arr)
			return (1);
		for (int i = 0; i < base->w * base->h; i++)
			base->arr[i] = shape;
		return (0);
	}
	return (1);
}

int	ft_ractangle(float x, float y, data *data)
{
	if ((x < data->x || y < data->y) || (data->x + data->w < x || data->y + data->h < y))
		return (0);
	if ((x - data->x < 1.00000000 || y - data->y < 1.00000000) || \
			(data->x + data->w - x < 1.00000000 || data->y + data->h - y < 1.00000000))
		return (2);
	return (1);
}

void	run_one(base *base, data *d, int x, int y)
{
	int is_in;

	is_in = ft_ractangle((float)x, (float)y, d);
	if (is_in == 2 || (is_in == 1 && d->type == 'R'))
		base->arr[x + y * base->w] = d->shape;
}


int	apply_info(data *d, base *base)
{
	if (d->w <= 0.00000000 || d->h <= 0.00000000 || (d->type != 'r' && d->type != 'R'))
		return (1);
	for (int i = 0; i < base->w; i++)
	{
		for (int j = 0; j < base->h; j++)
			run_one(base, d, i, j);
	}
	return (0);
}

void	print_info(base *base)
{
	for (int x = 0; x < base->h; x++)
	{
		write(1, (base)->arr + x * base->w, base->w);
		write(1, "\n", 1);
	}
}

int	run(FILE *file)
{
	data d;
	base base;
	int	ret;

	if (!get_info(&base, file))
	{
		ret = fscanf(file, "%c %f %f %f %f %c\n", &d.type, &d.x, &d.y, &d.w, &d.h, &d.shape);
		while (ret == 6)
		{
			if (apply_info(&d, &base))
				return (1);
			ret = fscanf(file, "%c %f %f %f %f %c\n", &d.type, &d.x, &d.y, &d.w, &d.h, &d.shape);
		}
		if (ret == -1)
		{
			print_info(&base);
			return (0);
		}
	}
	return (1);
}


int main(int ac, char **av)
{
	FILE *file;
	int len;
	if (ac == 2)
	{
		file = fopen(av[1], "r");
		if (file && !run(file))
			return (0);
		len = ft_strlen("Error: Operation file corrupted\n");
		write(1, "Error: Operation file corrupted\n", len);	
	}
	else
	{
		len = ft_strlen("Error: argument\n");
		write(1, "Error: argument\n", len);
	}
	return (1);
}
