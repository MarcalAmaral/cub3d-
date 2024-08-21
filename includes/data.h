/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:08:52 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/20 14:31:53 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
 #define DATA_H

#include <MLX42.h>

typedef enum s_texture
{
	NORTH = 0,
	SOUTH,
	WEST,
	EAST,
}			t_texture_index;

typedef	struct s_components_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	*wall[4];
}		t_comp_mlx;

typedef struct s_player
{
	double	pos[2];
	double	dir[2];
	double	plane[2];
}	t_plr;

typedef struct s_data
{
	t_comp_mlx	window;
	t_plr		*coord;
	char 		**worldmap;
	int			rgb_floor[4];
	int			rgb_cel[4];
}	t_data;


#endif