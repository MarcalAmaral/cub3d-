/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:48:30 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/20 13:42:17 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hook.h"
#include "data.h"
#include "parse.h"
#include "draw_image.h"
#include "MLX42.h"
#include "ray_casting.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	t_data	*data;

	data = parse(argc, argv);
	if (!data)
		return (EXIT_FAILURE);
		// return (error_handler("ERROR\n", NULL, NULL, NULL));
	draw_plaine(data);
	ray_casting(data);
	mlx_image_to_window(data->window.mlx, data->window.image, 0, 0);
	mlx_loop_hook(data->window.mlx, ft_hook, (void*)data);
	mlx_loop(data->window.mlx);
	mlx_terminate(data->window.mlx);
	ft_delcmtrx(data->worldmap);
	return (EXIT_SUCCESS);
}

