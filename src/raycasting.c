/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frushiti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:06:50 by frushiti          #+#    #+#             */
/*   Updated: 2024/06/28 18:07:03 by frushiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_get_texture_address(t_recup *recup)
{
	int	i;

	i = -1;
	while (++i < 5)
		recup->texture[i].addr = (int *)mlx_get_data_addr(recup->texture[i].img,
				&recup->texture[i].bits_per_pixel,
				&recup->texture[i].line_length, &recup->texture[i].endian);
}

void	ft_get_texture(t_recup *recup)
{
	void	*mlx_ptr;

	mlx_ptr = recup->data.mlx_ptr;
	recup->texture[0].img = mlx_xpm_file_to_image(mlx_ptr, recup->no,
			&(recup->texture[0].width), &(recup->texture[0].height));
	if (!recup->texture[0].img)
		ft_error(recup, "Texture SO\n");
	recup->texture[1].img = mlx_xpm_file_to_image(mlx_ptr, recup->so,
			&(recup->texture[1].width), &(recup->texture[1].height));
	if (!recup->texture[1].img)
		ft_error(recup, "Texture NO\n");
	recup->texture[2].img = mlx_xpm_file_to_image(mlx_ptr, recup->we,
			&(recup->texture[2].width), &(recup->texture[2].height));
	if (!recup->texture[2].img)
		ft_error(recup, "Texture EA\n");
	recup->texture[3].img = mlx_xpm_file_to_image(mlx_ptr, recup->ea,
			&(recup->texture[3].width), &(recup->texture[3].height));
	if (!recup->texture[3].img)
		ft_error(recup, "Texture WE\n");
	recup->texture[4].img = mlx_xpm_file_to_image(mlx_ptr, recup->sp,
			&(recup->texture[4].width), &(recup->texture[4].height));
	if (!recup->texture[4].img)
		ft_error(recup, "Texture S\n");
	ft_get_texture_address(recup);
}

int	ft_raycasting(t_recup *recup)
{
	recup->ray.x = -1;
	while (++recup->ray.x < recup->rx)
	{
		ft_initialisation3(recup);
		ft_stepsidedist(recup);
		ft_color_column(recup);
		recup->s.zbuffer[recup->ray.x] = recup->ray.perpwalldist;
	}
	ft_sprite(recup);
	if (recup->save == 1)
		ft_save(recup);
	mlx_put_image_to_window(recup->data.mlx_ptr, recup->data.mlx_win,
		recup->data.img, 0, 0);
	ft_forward_back(recup);
	ft_left_right(recup);
	ft_rotate_right_left(recup);
	ft_swap(recup);
	return (0);
}

int	ft_mlx(t_recup *recup)
{
	ft_initialisation2(recup);
	recup->data.mlx_ptr = mlx_init();
	if (!recup->data.mlx_ptr)
		ft_error(recup, "Mlx init impossible\n");
	mlx_get_screen_size(recup->data.mlx_ptr, &recup->screenx, &recup->screeny);
	if (recup->rx > recup->screenx)
		recup->rx = recup->screenx;
	if (recup->ry > recup->screeny)
		recup->ry = recup->screeny;
	ft_get_texture(recup);
	recup->data.img = mlx_new_image(recup->data.mlx_ptr, recup->rx, recup->ry);
	recup->data.addr = (int *)mlx_get_data_addr(recup->data.img, &recup->data
			.bits_per_pixel, &recup->data.line_length, &recup->data.endian);
	if (recup->save == 1)
		ft_raycasting(recup);
	recup->data.mlx_win = mlx_new_window(recup->data.mlx_ptr, recup->rx,
			recup->ry, "shqipee rawr");
	recup->data.img2 = mlx_new_image(recup->data.mlx_ptr, recup->rx, recup->ry);
	recup->data.addr2 = (int *)mlx_get_data_addr(recup->data.img2,
			&recup->data.bits_per_pixel, &recup->data.line_length,
			&recup->data.endian);
	mlx_hook(recup->data.mlx_win, 33, 1L << 17, ft_exit, recup);
	mlx_hook(recup->data.mlx_win, 2, 1L << 0, ft_key_press, recup);
	mlx_loop_hook(recup->data.mlx_ptr, ft_raycasting, recup);
	mlx_hook(recup->data.mlx_win, 3, 1L << 1, ft_key_release, recup);
	mlx_loop(recup->data.mlx_ptr);
	return (0);
}
