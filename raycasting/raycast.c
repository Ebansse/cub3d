/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:28:31 by ebansse           #+#    #+#             */
/*   Updated: 2025/10/08 15:48:09 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	wall_hit(t_config *game, float ray_x, float ray_y)
{
	if (game->wall_o == NORTH || game->wall_o == SOUTH)
		game->wall_hit = ray_x - floor(ray_x / BLOCK) * BLOCK;
	else
		game->wall_hit = ray_y - floor(ray_y / BLOCK) * BLOCK;
	game->tex_x = (int)(game->wall_hit
			* game->textures[game->wall_o].width / BLOCK);
	if (game->wall_o == SOUTH || game->wall_o == WEST)
		game->tex_x = game->textures[game->wall_o].width - game->tex_x - 1;
}

void	draw_wall(t_config *game, float ray_x, float ray_y, int i)
{
	float	dist;
	float	height;
	int		start_y;
	int		end;
	int		color;

	dist = fixed_dist(ray_x - game->player.x, ray_y - game->player.y, game);
	height = (BLOCK / dist) * (WIN_W / 2);
	start_y = (WIN_H - height) / 2;
	end = start_y + height;
	wall_hit(game, ray_x, ray_y);
	while (start_y < end)
	{
		game->tex_y = ((start_y - (WIN_H - height) / 2)
				* game->textures[game->wall_o].height) / height;
		color = get_texture_pixel(&game->textures[game->wall_o],
				game->tex_x, game->tex_y);
		put_pixel(i, start_y, color, &game->frame);
		start_y++;
	}
}

void	orientation(float ray_x, float cos, float sin, t_config *game)
{
	if ((int)(ray_x / BLOCK) != (int)((ray_x - cos) / BLOCK))
	{
		if (cos > 0)
			game->wall_o = EAST;
		else
			game->wall_o = WEST;
	}
	else
	{
		if (sin > 0)
			game->wall_o = SOUTH;
		else
			game->wall_o = NORTH;
	}
}

void	draw_line(t_player *player, t_config *game, float start_x, int i)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
	ray_y = player->y;
	while (!touch(ray_x, ray_y, game))
	{
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	orientation(ray_x, cos_angle, sin_angle, game);
	draw_wall(game, ray_x, ray_y, i);
}

int	draw_loop(t_config *game)
{
	float	fraction;
	float	start_x;
	int		i;

	move_player(&game->player, game);
	clear_img(game);
	draw_floor_ceiling(game);
	fraction = PI / 3 / WIN_W;
	start_x = game->player.angle - PI / 6;
	i = 0;
	while (i < WIN_W)
	{
		draw_line(&game->player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->frame.img, 0, 0);
	return (0);
}
