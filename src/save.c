/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frushiti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:08:55 by frushiti          #+#    #+#             */
/*   Updated: 2024/06/28 18:08:57 by frushiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_header(t_recup *recup, int fd)
{
	int	tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * recup->rx * recup->ry;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &recup->rx, 4);
	write(fd, &recup->ry, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &recup->data.bits_per_pixel, 2);
	tmp = 0;
	write(fd, &tmp, 4 * 6);
}

void	ft_save(t_recup *recup)
{
	int	fd;
	int	x;
	int	y;

	y = recup->ry - 1;
	fd = open("./image.bmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		ft_error(recup, "Impossible to create .bmp\n");
	ft_header(recup, fd);
	while (y >= 0)
	{
		x = 0;
		while (x < recup->rx)
		{
			write(fd, &recup->data.addr[y * recup->rx + x], 4);
			x++;
		}
		y--;
	}
	close(fd);
	ft_error(recup, "OK--save ok\n");
}

int	ft_check_save(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len >= 6 && str[len - 1] == 'e' && str[len - 2] == 'v'
		&& str[len - 3] == 'a' && str[len - 4] == 's' && str[len - 5] == '-'
		&& str[len - 6] == '-')
		return (1);
	return (0);
}

int	ft_nb_virgule(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ',')
			count++;
		str++;
	}
	return (count);
}
