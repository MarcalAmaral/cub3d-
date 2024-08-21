/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_texture.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 08:54:40 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/18 11:47:20 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXELS_TEXTURE_H
 #define PIXELS_TEXTURE_H

typedef struct s_ray_casting t_ray;
typedef struct s_data t_data;
typedef struct s_dda t_dda;

int	buffer_pixel_texture(t_data *data, t_dda *dda, t_ray *ray);

#endif