/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:15:00 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/22 14:59:52 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>
#include <../lib/MLX42/include/MLX42/MLX42.h>
#include "libft.h"

int ft_color(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int 	display_error(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
		ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
		ft_putstr_fd(s2, STDERR_FILENO);
	if (s3)
		ft_putstr_fd(s3, STDERR_FILENO);
	if (s4)
		ft_putstr_fd(s4, STDERR_FILENO);
	return (1);
}
