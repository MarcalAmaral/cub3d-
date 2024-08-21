/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 08:54:40 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/18 11:40:41 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_H
 #define DDA_H

typedef struct s_data t_data;
typedef struct s_ray_casting t_ray;

typedef struct s_dda
{
	int		hit;
	int		side;
	int		step[2];
	int		map[2];
	double	side_dist[2];
	double	delta_dist[2];
}		t_dda;

void ft_dda(t_data *data, t_ray *ray, t_dda *dda);

#endif