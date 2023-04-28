#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

typedef struct base
{
	int w;
	int h;
	char *arr;
}base;

typedef struct data
{
	char type;
	float x;
	float y;
	float r;
	char shape;

}	 data;

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int	get_info(base *base, FILE *file)
{
	int	ret;
	char ch;
	char *tmp;

	ret = fscanf(file, "%d %d %c\n", &base->w, &base->h, &ch);
	if (ret == 3)
	{
		if ((base->w < 0 || base->h < 0) || (base->w > 300 || base->h > 300))
			return (1);
		tmp = malloc(base->w * base->h);
		base->arr = tmp;
		if (!base->arr)
			return (1);
		for (int x = 0; x < base->w * base->h; x++)
			base->arr[x] = ch;
		return (0);
	}
	return (1);
}


float square(float a)
{
	return (a * a);
}

float dis_sq(float x1, float y1, float x2, float y2)
{
	float lenx;
	float leny;

	lenx = square(x1 - x2);
	leny = square(y1 - y2);
	return (lenx + leny);
}

int	ft_circle(float x, float y, data *data)
{
	float	distance_sq;
	float	distance;

	distance_sq = sqrtf(dis_sq(x, y, data->x, data->y));
	distance = distance_sq - data->r;
	if (distance <= 0.00000000)
	{
		if (distance <= -1.00000000)
			return (1);
		return (2);
	}
	return (0);
}
void	run_one(base *base, data *data, int x, int y)
{
	int is_in;

	is_in = ft_circle((float)x, (float)y, data);
	if (is_in == 2 || (is_in == 1 && data->type == 'C'))
		base->arr[x + y * base->w] = data->shape;
}

int	apply_info(base *base, data *data)
{
	if (data->r <= 0.00000000 || (data->type != 'c' && data->type != 'C'))
		return (1);
	for (int i = 0; i < base->w; i++)
	{
		for (int j = 0; j < base->h; j++)
			run_one(base, data, i, j);
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
	data data;
	base base;
	int	ret;

	if (!get_info(&base, file))
	{
		ret = fscanf(file, "%c %f %f %f %c\n", &data.type, &data.x, &data.y, &data.r, &data.shape);
		while (ret == 5)
		{
			if (apply_info(&base, &data))
				return (1);
			ret = fscanf(file, "%c %f %f %f %c\n", &data.type, &data.x, &data.y, &data.r, &data.shape);
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
		len = ft_strlen("Error ~~\n");
		write(1, "Error ~~\n", len);
	}
	else
	{
		len = ft_strlen("Error argument\n");
		write(1, "Error argument\n", len);
	}
	return (1);
}
