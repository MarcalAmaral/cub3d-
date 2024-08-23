/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.validations.rgb.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:55:41 by myokogaw          #+#    #+#             */
/*   Updated: 2024/08/22 13:55:41 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "data.h"
#include "parse.h"
#include "validation/validations.h"
#include "error/error.h"
#include "libft.h"

#include <stdio.h>

int	check_rgb_values(t_parser *parser);
int	set_error(t_parser *parser, enum e_parser_errors error, int matrix_index);
int	check_rgb_format_cub(t_parser *parser);
void	setting_rgb_values(t_parser *parser);
void	check_rgb_pattern(t_parser *parser);

void	get_rgb_matrix(t_parser *parser)
{
	if (parser->meta.rgb_matrix != NULL)
		ft_delcmtrx(parser->meta.rgb_matrix);
	// printf("rgb_matrix lenght %d\n", ft_mtrxlen(parser->meta.rgb_matrix));
	parser->meta.rgb_matrix = ft_split(parser->meta.content_id_str, ',');
	if (parser->meta.rgb_matrix == NULL)
		parser->error = E_MEM_RGB_MATRIX;
	format_memalloc_error(parser);
}

int	validating_rgb(t_parser *parser)
{
	get_rgb_matrix(parser);
	check_rgb_pattern(parser);
	setting_rgb_values(parser);
	return (EXIT_SUCCESS);
}

int	has_three_octets(t_parser *parser)
{
	// printf("rgb_matrix lenght %d\n", ft_mtrxlen(parser->meta.rgb_matrix));
	if (ft_mtrxlen(parser->meta.rgb_matrix) != 3)
	{
		parser->error = E_RGB_INVAMOUNT;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	check_rgb_pattern(t_parser *parser)
{
	int	error_occurred;

	error_occurred = false;
	// printf("ident %c, quantity of elements %d and values %s %s %s\n", *parser->meta.start_id_str, ft_mtrxlen(parser->meta.rgb_matrix), parser->meta.rgb_matrix[0], parser->meta.rgb_matrix[1], parser->meta.rgb_matrix[2]);
	if (has_three_octets(parser)) // Checa se tem 3 octetos
		error_occurred = true;
	else if (!error_occurred && check_rgb_format_cub(parser)) // Checa se esta no formato rgb (0 a 255) para o projeto cub3D
		error_occurred = true;
	else if (!check_rgb_id_dup(parser) && !error_occurred && check_rgb_values(parser)) // Checa se não repetiu um id e se os valores passados no rgb estão entre 0 e 255
		error_occurred = true;
	format_rgb_error(parser);
}

int	check_rgb_format_cub(t_parser *parser)
{
	int	str_index;
	int	c_index;

	str_index = -1;
	while (parser->meta.rgb_matrix[++str_index])
	{
		c_index = 0;
		while (parser->meta.rgb_matrix[str_index][c_index]
			&& ft_isdigit(parser->meta.rgb_matrix[str_index][c_index]))
			c_index++;
		if (parser->meta.rgb_matrix[str_index][c_index] != '\0')
			return (set_error(parser, E_RGB_DIGIT, str_index));
		else if (c_index > 3)
			return (set_error(parser, E_RGB_INVRANGE, str_index));
	}
	return (EXIT_SUCCESS);
}


int	set_error(t_parser *parser, enum e_parser_errors error, int matrix_index)
{
	if (matrix_index != -1)
		parser->meta.rgb_str_index = matrix_index;
	parser->error = error;
	return (EXIT_FAILURE);
}

void	setting_rgb_values(t_parser *parser)
{
	int	matrix_index;
	int	color;

	matrix_index = -1;
	while (parser->meta.rgb_matrix[++matrix_index])
	{
		color = ft_atoi(parser->meta.rgb_matrix[matrix_index]);
		if (*parser->meta.start_id_str == 'C')
			parser->ceiling_rgb[matrix_index] = color;
		else if (*parser->meta.start_id_str == 'F')
			parser->floor_rgb[matrix_index] = color;
	}
	if (*parser->meta.start_id_str == 'C')
		parser->ceiling_rgb[3] = true;
	else if (*parser->meta.start_id_str == 'F')
		parser->floor_rgb[3] = true;
}

int		check_rgb_values(t_parser *parser)
{
	int	matrix_index;
	int	color;

	matrix_index = -1;
	while (parser->meta.rgb_matrix[++matrix_index])
	{
		color = ft_atoi(parser->meta.rgb_matrix[matrix_index]);
		if (color < 0 || color > 255)
			return (set_error(parser, E_RGB_INVRANGE, matrix_index));
	}
	return (EXIT_SUCCESS);
}
