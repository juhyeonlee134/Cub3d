/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:48:12 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/17 12:03:13 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	exit_program(void)
{
	exit(0);
	return (0);
}

int	key_handling(int keycode, t_game *const game)
{
	if (keycode == ESC_KEY)
		exit(1);
	if (keycode == RIGHT)
		game->turn_right = 1;
	else if (keycode == LEFT)
		game->turn_left = 1;
	else if (keycode == W)
		game->move_front = 1;
	else if (keycode == S)
		game->move_back = 1;
	else if (keycode == D)
		game->move_right = 1;
	else if (keycode == A)
		game->move_left = 1;
	return (0);
}

int	door_handling(int keycode, t_game *const game)
{
	int	x;
	int	y;

	if (keycode == 14)
	{
		x = game->posx + game->dirx;
		y = game->posy + game->diry;
		if (game->map.map[y][x] == 'D')
			game->map.map[y][x] = 'O';
		else if (game->map.map[y][x] == 'O')
			game->map.map[y][x] = 'D';
	}
	render(game);
	return (0);
}

void	turn_right(t_game *const game)
{
	double const	olddirx = game->dirx;
	double const	olddiry = game->diry;
	double const	oldplanx = game->planx;
	double const	oldplany = game->plany;

	game->dirx = olddirx * cos(ANGLE) - olddiry * sin(ANGLE);
	game->diry = olddirx * sin(ANGLE) + olddiry * cos(ANGLE);
	game->planx = oldplanx * cos(ANGLE) - oldplany * sin(ANGLE);
	game->plany = oldplanx * sin(ANGLE) + oldplany * cos(ANGLE);
}

void	turn_left(t_game *const game)
{
	double const	olddirx = game->dirx;
	double const	olddiry = game->diry;
	double const	oldplanx = game->planx;
	double const	oldplany = game->plany;

	game->dirx = olddirx * cos(-ANGLE) - olddiry * sin(-ANGLE);
	game->diry = olddirx * sin(-ANGLE) + olddiry * cos(-ANGLE);
	game->planx = oldplanx * cos(-ANGLE) - oldplany * sin(-ANGLE);
	game->plany = oldplanx * sin(-ANGLE) + oldplany * cos(-ANGLE);
}

void	move_forward(t_game *const game)
{
	t_move	m;

	m.diffx = game->posx + game->dirx * SPEED;
	m.diffy = game->posy + game->diry * SPEED;
	m.collx = (-SPEED) * (game->dirx < 0) + SPEED * (game->dirx > 0);
	m.colly = (-SPEED) * (game->diry < 0) + SPEED * (game->diry > 0);
	m.leftx = game->posx + game->diry * COLL + game->dirx * SPEED;
	m.lefty = game->posy - game->dirx * COLL + game->diry * SPEED;
	m.rightx = game->posx - game->diry * COLL + game->dirx * SPEED;
	m.righty = game->posy + game->dirx * COLL + game->diry * SPEED;
	if (game->map.map[(int)m.lefty][(int)(m.leftx + m.collx)] != '1' \
	&& game->map.map[(int)m.righty][(int)(m.rightx + m.collx)] != '1' \
	&& game->map.map[(int)game->posy][(int)(m.diffx + m.collx)] != '1' \
	&& game->map.map[(int)m.lefty][(int)(m.leftx + m.collx)] != 'D' \
	&& game->map.map[(int)m.righty][(int)(m.rightx + m.collx)] != 'D' \
	&& game->map.map[(int)game->posy][(int)(m.diffx + m.collx)] != 'D')
		game->posx = m.diffx;
	if (game->map.map[(int)(m.lefty + m.colly)][(int)m.leftx] != '1' \
	&& game->map.map[(int)(m.righty + m.colly)][(int)m.rightx] != '1' \
	&& game->map.map[(int)(m.diffy + m.colly)][(int)game->posx] != '1' \
	&& game->map.map[(int)(m.lefty + m.colly)][(int)m.leftx] != 'D' \
	&& game->map.map[(int)(m.righty + m.colly)][(int)m.rightx] != 'D' \
	&& game->map.map[(int)(m.diffy + m.colly)][(int)game->posx] != 'D')
		game->posy = m.diffy;
}