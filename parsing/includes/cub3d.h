/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:43:32 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/09 13:09:33 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>

# define BUFF_SZ 31

# define HEIGHT 1080
# define WIDTH 1920

# define TXT_WIDTH 32
# define ESC_KEY 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124
# define KEY_EXIT 17
# define KEY_PRESS 2
# define FOV 0.87

# define ANGLE 0.1
# define SPEED 0.3
# define COLLISION 0.5

enum e_error
{
	E_ALLOC,
	E_ARG_LACK,
	E_ARG_MANY,
	E_FILE_INVAL,
	E_FILE_FDERR,
	E_RSRC_LACK,
	E_TYPE_INVAL,
	E_TEXT_NOTFD,
	E_TEXT_MANY,
	E_COL_NOTFD,
	E_COL_LACK,
	E_COL_MANY,
	E_COL_INVAL,
	E_PNG_FAIL,
	E_MAP_NOTFD,
	E_MAP_OTHEL,
	E_MAP_INVAL,
	E_MAP_2PLAYER,
	E_MAP_NOPLAYER,
	E_MLX
};

typedef enum e_type
{
	T_NL = -1,
	T_NO,
	T_SO,
	T_WE,
	T_EA,
	T_FL,
	T_CL
}t_type;

typedef unsigned int	t_color;

typedef struct s_resource
{
	char		*textures[4];
	t_color		colors[2][3];
	t_color 	fl_color;
	t_color 	cl_color;
}t_rsrc;

typedef struct s_map
{
	char	**map;
	size_t	h;
	size_t	w;
}t_map;

typedef struct s_img
{
	void	*obj;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
	int		w;
	int		h;
}t_img;

typedef struct s_game
{
	t_rsrc rsrc;
	t_map map;
	
	void	*mlx;
	void	*win;
	
	t_img	screen;
	t_img	textures[4];

	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planx;
	double	plany;
}t_game;

void	print_error(enum e_error num);
void	resource_error(enum e_error num);
void	map_error(enum e_error num);

char	*get_line(int const fd);
int		not_contain_nl(char const *str);
char	*merge(char *const s1, char const *const s2);
char	*extract(char const *const str);
void	organize(char *const str);

void	init_window(void *mlx, void *win, t_img *img, t_rsrc *rsrc);
void	set_position(t_game *game, char **map);
void	set_png_images(t_game *game, t_img *ts, int i);
void	set_images(t_game *game, t_img *sc, t_img *ts);
void	load_window(t_game *game);

/* parsing */
void	parse(t_map *const map, t_rsrc *const rsrc, \
			char const *const file_name);
int		open_file(char const *const file_name);

void	init_resource(t_rsrc *const rsrc, int const fd);
t_type	get_type(char const *str);
int		is_white(char const ch);
char	*set_texture(char const *str);
void	set_color(t_color *const color, char const *str);
t_color	convert_color(char const *const str);
void	clear_resource(t_rsrc *const rsrc);

void	init_map(t_map *const map, int const fd);
size_t	get_start_point(char const *str);
void	get_map_size(t_map *const map, char const *str);
void	convert_map(t_map *const map, char const *str);
size_t	get_line_len(char const *str);
void	check_elements(t_map const map);
int		is_player(char const el);
int		check_player(char const el);
void	check_surround(t_map const map);
void	find_player(t_map const map, size_t *const y, size_t *const x);
void	copy_map(t_map *const dst, t_map const org);
void	clear_map(t_map const map);
void	check_around(t_map const map, size_t const y, size_t const x);
int		check_up(t_map const map, size_t const y, size_t const x);
int		check_left(t_map const map, size_t const y, size_t const x);
int		check_down(t_map const map, size_t const y, size_t const x);
int		check_right(t_map const map, size_t const y, size_t const x);

#endif
