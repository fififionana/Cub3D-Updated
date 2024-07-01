/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_move.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frushiti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:33:55 by frushiti          #+#    #+#             */
/*   Updated: 2024/06/28 17:34:00 by frushiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_forward_back(t_recup *recup)
{
	double	move_speed;

	move_speed = recup->ray.movespeed * 2;
	if (recup->data.forward == 1)
	{
		if (recup->map[(int)(recup->ray.posx + recup->ray.dirx
				* move_speed)][(int)recup->ray.posy] == '0')
			recup->ray.posx += recup->ray.dirx * recup->ray.movespeed;
		if (recup->map[(int)recup->ray.posx][(int)(recup->ray.posy
			+ recup->ray.diry * move_speed)] == '0')
			recup->ray.posy += recup->ray.diry * recup->ray.movespeed;
	}
	if (recup->data.back == 1)
	{
		if (recup->map[(int)(recup->ray.posx - recup->ray.dirx
				* move_speed)][(int)recup->ray.posy] == '0')
			recup->ray.posx -= recup->ray.dirx * recup->ray.movespeed;
		if (recup->map[(int)recup->ray.posx][(int)(recup->ray.posy
			- recup->ray.diry * move_speed)] == '0')
			recup->ray.posy -= recup->ray.diry * recup->ray.movespeed;
	}
}

void	ft_left_right(t_recup *recup)
{
	double	move_speed;

	move_speed = recup->ray.movespeed * 2;
	if (recup->data.right == 1)
	{
		if (recup->map[(int)(recup->ray.posx + recup->ray.diry
				* move_speed)][(int)recup->ray.posy] == '0')
			recup->ray.posx += recup->ray.diry * recup->ray.movespeed;
		if (recup->map[(int)recup->ray.posx][(int)(recup->ray.posy
			- recup->ray.dirx * move_speed)] == '0')
			recup->ray.posy -= recup->ray.dirx * recup->ray.movespeed;
	}
	if (recup->data.left == 1)
	{
		if (recup->map[(int)(recup->ray.posx - recup->ray.diry
				* move_speed)][(int)recup->ray.posy] == '0')
			recup->ray.posx -= recup->ray.diry * recup->ray.movespeed;
		if (recup->map[(int)recup->ray.posx][(int)(recup->ray.posy
			+ recup->ray.dirx * move_speed)] == '0')
			recup->ray.posy += recup->ray.dirx * recup->ray.movespeed;
	}
}

void	ft_rotate_right_left_2(t_recup *recup)
{
	double	old_dirx;
	double	old_planx;
	double	rot_speed;

	old_dirx = recup->ray.dirx;
	old_planx = recup->ray.planx;
	rot_speed = recup->ray.rotspeed / 2;
	if (recup->data.rotate_right == 1)
	{
		recup->ray.dirx = recup->ray.dirx * cos(-rot_speed)
			- recup->ray.diry * sin(-rot_speed);
		recup->ray.diry = old_dirx * sin(-rot_speed)
			+ recup->ray.diry * cos(-rot_speed);
		recup->ray.planx = recup->ray.planx * cos(-rot_speed)
			- recup->ray.plany * sin(-rot_speed);
		recup->ray.plany = old_planx * sin(-rot_speed)
			+ recup->ray.plany * cos(-rot_speed);
	}
}

void	ft_rotate_right_left(t_recup *recup)
{
	double	old_dirx;
	double	old_planx;
	double	rot_speed;

	old_dirx = recup->ray.dirx;
	old_planx = recup->ray.planx;
	rot_speed = recup->ray.rotspeed / 2;
	ft_rotate_right_left_2(recup);
	if (recup->data.rotate_left == 1)
	{
		recup->ray.dirx = recup->ray.dirx * cos(rot_speed)
			- recup->ray.diry * sin(rot_speed);
		recup->ray.diry = old_dirx * sin(rot_speed)
			+ recup->ray.diry * cos(rot_speed);
		recup->ray.planx = recup->ray.planx * cos(rot_speed)
			- recup->ray.plany * sin(rot_speed);
		recup->ray.plany = old_planx * sin(rot_speed)
			+ recup->ray.plany * cos(rot_speed);
	}
}
