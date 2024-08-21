/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 08:58:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/13 15:40:55 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CASTING_H
 #define RAY_CASTING_H

typedef struct s_ray_casting
{
	int		index;
	double	camX;
	double	ray_dir[2];
	double	distance_wall;
	int		line_height;
	int		draw_start;
	int		draw_end;
}		t_ray;

void	ray_casting(t_data *data);

#endif