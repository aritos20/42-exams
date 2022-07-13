/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:13:07 by agianico          #+#    #+#             */
/*   Updated: 2020/10/15 17:44:15 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "micro_paint.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_error(char *err)
{
	write(1, err, ft_strlen(err));
	return (1);
}

int		ft_get_zone(int ret, t_zone zone)
{
	if (ret != 3 || zone.width <= 0 || zone.width > 300 ||
	zone.height <= 0 || zone.height > 300)
		return (ft_error("Error: Operation file corrupted\n"));
	return (0);
}

int		ft_get_shape(int ret, t_shape shape)
{
	if (ret != 6 || (shape.type != 'r' && shape.type != 'R') ||
	shape.width <= 0 || shape.height <= 0)
		return (ft_error("Error: Operation file corrupted\n"));
	return (0);
}

char	*ft_background(t_zone zone)
{
	char	*drawing;
	int		i;

	i = 0;
	if (!(drawing = (char *)malloc(sizeof(*drawing) * (zone.width * zone.height))))
		return (0);
	while (i < zone.width * zone.height)
		drawing[i++] = zone.background;
	return (drawing);
}

int		ft_isinside(t_shape shape, int i, int j)
{
	if (i >= shape.y && i <= shape.y + shape.height &&
	j >= shape.x && j <= shape.x + shape.width)
	{
		if ((i - shape.y) < 1.00000000 || (j - shape.x) < 1.00000000 ||
		(shape.y + shape.height - i) < 1.00000000 || (shape.x + shape.width - j) < 1.00000000)
			return (2);
		return (1);	
	}
	return (0);
}

char	*ft_fill(t_zone zone, t_shape shape, char *drawing)
{
	int i;
	int j;

	i = 0;
	while (i < zone.height)
	{
		j = 0;
		while (j < zone.width)
		{
			if ((ft_isinside(shape, i, j) > 0 && shape.type == 'R')
			|| (shape.type == 'r' && ft_isinside(shape, i, j) == 2))
				drawing[(i * zone.width) + j] = shape.color;
			j++;
		}
		i++;
	}
	return (drawing);
}

void	ft_printer(t_zone zone, char *drawing)
{
	int i;

	i = 0;
	while (i < zone.height)
	{
		write(1, drawing + (i * zone.width), zone.width);
		write(1, "\n", 1);
		i++;
	}
}

int		main(int argc, char **argv)
{
	FILE	*fd;
	int		ret;
	t_zone	zone;
	t_shape	shape;
	char	*drawing;

	if (argc != 2)
		return (ft_error("Error: argument\n"));
	if (!(fd = fopen(argv[1], "r")))
		return (ft_error("Error: Operation file corrupted\n"));
	ret = fscanf(fd, "%d %d %c\n", &zone.width, &zone.height, &zone.background);
	if (ft_get_zone(ret, zone) == 1)
		return (1);
	if (!(drawing = ft_background(zone)))
		return (ft_error("Malloc error"));
	while ((ret = fscanf(fd, "%c %f %f %f %f %c\n", &shape.type,
	&shape.x, &shape.y, &shape.width, &shape.height, &shape.color)) > 0)
	{
		if (ft_get_shape(ret, shape) == 1)
			return (1);
		drawing = ft_fill(zone, shape, drawing);
	}
	ft_printer(zone, drawing);
	free(drawing);
	return (0);
}
