/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:49:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/21 18:51:25 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "data.h"
#include "utils.h"
#include <MLX42.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>
#include "defines.h"
#include <math.h>
#include <string.h>
#include <errno.h>
#include "parse.h"


// Validações para serem realizadas:
// 	Primeira validação: Argumentos recebidos (int argc, char **av)
// 		Validar quantidade de argumentos recebidos, o programa recebe no máximo dois e no mínimo dois argumentos
// 		Validar se o argumento recebido possui extensão .cub
//		Validar se o filename passado não é um diretório e se é possível abrir para ler o arquivo
// 	Segunda validação: Validar as informações do arquivo .cub fornecido
// 		Validar se o arquivo contempla todas as informações necessárias
// 		Validar se não há valores repetidos tanto para os identificadores
// 		Validar se possui uma textura diferente para cada direção cardial
//		Validar se os identificadores das texturas são NO, SO, WE, EA
// 		Validar se as cores rgb dos identificadores C e F estão formatadas corretamente
// 		Validar se o mapa é composto somente por 1 e 0 e o player (NSWE)
// 		Validar se o mapa no qual o player (NSWE) se encontra está fechado por paredes


static int	init_data(t_data *data);
// static char **cpy_file(char *file);
static void	init_coord(t_plr *coord, t_data *data);
void		clean_parser_struct(t_parser *parser);
void		clean_line_metadata_struct(t_line_meta *metadata);
void		set_texture_pathname(t_parser *parser, t_line_meta *metadata, t_texture_index identifier, int lenght_identifier);

void	error_arguments(t_parser *parser)
{
	if (parser->error == E_OK)
		return ;
	else if (parser->error == E_ARG_INVNUM)
		error_handler(ERROR_MSG, "Invalid number of arguments\n", NULL, NULL);
	else if (parser->error == E_ARG_INVEXT)
		error_handler(ERROR_MSG,
			"Invalid path, path with .cub extension required\n", NULL, NULL);
	exit (EXIT_FAILURE);
}

void	validating_arguments(t_parser *parser, int ac, char **av)
{
	if (ac != 2)
		parser->error = E_ARG_INVNUM;
	else if (ft_strlen(av[1]) < 4 || ft_strnstr(&(av[1][ft_strlen(av[1]) - 4]), ".cub", 4) == NULL)
		parser->error = E_ARG_INVEXT;
	error_arguments(parser);
	parser->pathname = ft_strdup(av[1]);
}

void	error_file(t_parser *parser)
{
	if (parser->error == E_OK)
		return ;
	else if (parser->error == E_FILE_ISDIR)
		error_handler(ERROR_MSG, strerror(EISDIR), "\n", NULL);
	else if (parser->error == E_FILE_FAILOPEN)
		error_handler(ERROR_MSG, strerror(errno), "\n", NULL);
	if (parser->fd != -1)
		close(parser->fd);
	exit (EXIT_FAILURE);
}

void	validating_file(t_parser *parser)
{
	parser->fd = open(parser->pathname, O_DIRECTORY);
	if (parser->fd != FAIL)
		parser->error = E_FILE_ISDIR;
	parser->fd = open(parser->pathname, O_RDONLY);
	if (parser->fd == FAIL)
		parser->error = E_FILE_FAILOPEN;
	error_file(parser);
}

int	validating_rgb_format(t_parser *parser, t_line_meta *metadata)
{
	int	matrix_index;
	int	char_index;

	matrix_index = 0;
	while (metadata->rgb_matrix[matrix_index])
	{
		char_index = 0;
		while (metadata->rgb_matrix[matrix_index][char_index] && ft_isdigit(metadata->rgb_matrix[matrix_index][char_index]))
			char_index++;
		if (metadata->rgb_matrix[matrix_index][char_index] != '\0')
		{
			metadata->rgb_matrix_index = matrix_index;
			metadata->rgb_char_index = char_index;
			parser->error = E_RGB_DIGIT;
			return (EXIT_FAILURE);
		}
		else if (char_index > 3)
		{
			metadata->rgb_matrix_index = matrix_index;
			metadata->rgb_char_index = char_index;
			parser->error = E_RGB_INVRANGE;
			return (EXIT_FAILURE);
		}
		matrix_index++;
	}
	return (EXIT_SUCCESS);
}


int		validating_rgb_values(t_parser *parser, t_line_meta *metadata)
{
	int	matrix_index;
	int	rgb_color;

	matrix_index = -1;
	while (metadata->rgb_matrix[++matrix_index])
	{
		rgb_color = ft_atoi(metadata->rgb_matrix[matrix_index]);
		if (rgb_color < 0 || rgb_color > 255)
		{
			metadata->rgb_matrix_index = matrix_index;
			parser->error = E_RGB_INVRANGE;
			return (EXIT_FAILURE);
		}
		if (*metadata->start_identifier_str == 'C')
			parser->rgb_array[CEILING][matrix_index] = rgb_color;
		else if (*metadata->start_identifier_str == 'F')
			parser->rgb_array[FLOOR][matrix_index] = rgb_color;
	}
	return (EXIT_SUCCESS);
}

void print_wrong_elem_rgb_matrix(t_line_meta *metadata)
{
	int		matrix_index;
	int		wrong_element;
	char	identifier[2];

	wrong_element = metadata->rgb_matrix_index;
	identifier[0] = *metadata->start_identifier_str;
	identifier[1] = ' ';
	write(STDERR_FILENO, identifier, 2);
	matrix_index = 0;
	while (metadata->rgb_matrix[matrix_index])
	{
		if (matrix_index != wrong_element && metadata->rgb_matrix[matrix_index + 1] != NULL)
			error_handler(metadata->rgb_matrix[matrix_index], ",", NULL, NULL);
		else if (matrix_index != wrong_element && metadata->rgb_matrix[matrix_index + 1] == NULL)
			error_handler(metadata->rgb_matrix[matrix_index], "\n", NULL, NULL);
		else if (matrix_index == wrong_element && metadata->rgb_matrix[matrix_index + 1] != NULL)
			error_handler(RED, metadata->rgb_matrix[matrix_index], RESET, ",");
		else if (matrix_index == wrong_element && metadata->rgb_matrix[matrix_index + 1] == NULL)
			error_handler(RED, metadata->rgb_matrix[matrix_index], RESET, "\n");
		matrix_index++;
	}
}

void	err_msg_rgb(t_parser *parser, t_line_meta *metadata)
{
	char	*num_line_str;

	if (parser->error == E_OK)
		return ;
	num_line_str = ft_itoa(parser->num_line);
	if (parser->error == E_RGB_INVAMOUNT)
	{
		error_handler(ERROR_MSG, "invalid quantity of elements to represent an RGB value: line ", num_line_str, ": ");
		print_wrong_elem_rgb_matrix(metadata);
	}
	else if (parser->error == E_RGB_DIGIT)
	{
		error_handler(ERROR_MSG, "just digits is needed to represent RGB colors: line ", num_line_str, ": ");
		print_wrong_elem_rgb_matrix(metadata);
	}
	else if (parser->error == E_RGB_INVRANGE)
	{
		error_handler(ERROR_MSG, "invalid range for rgb values, needed 0 <= value >= 255: line ", num_line_str, ": ");
		print_wrong_elem_rgb_matrix(metadata);
	}
	free(num_line_str);
	clean_parser_struct(parser);
	clean_line_metadata_struct(metadata);
	exit (EXIT_FAILURE);
}

void	validating_rgb_pattern(t_parser *parser, t_line_meta *metadata)
{
	int	condition_met;

	condition_met = 0;
	if (ft_mtrxlen(metadata->rgb_matrix) != 3)
	{
		parser->error = E_RGB_INVAMOUNT;
		condition_met = 1;
	}
	else if (!condition_met && validating_rgb_format(parser, metadata))
		condition_met = 1;
	else if (!condition_met && validating_rgb_values(parser, metadata))
		condition_met = 1;
	err_msg_rgb(parser, metadata);
}

int	validating_rgb(t_parser *parser, t_line_meta *metadata)
{
	char	*rgb_string;

	rgb_string = ft_strtrim((const char *) metadata->end_identifier_str, " \t\r\n");
	metadata->rgb_matrix = ft_split(rgb_string, ',');
	free(rgb_string);
	if (metadata->rgb_matrix == NULL)
		return (EXIT_FAILURE);
	validating_rgb_pattern(parser, metadata);
	return (EXIT_SUCCESS);
}

void	validating_line(t_parser *parser, t_line_meta *line_metadata)
{
	line_metadata->line = get_next_line(parser->fd);
	parser->num_line += 1;
	while (line_metadata->line)
	{
		if ((ft_strlen(line_metadata->line) == 1 && !ft_strncmp(line_metadata->line, "\n", 1))
			|| (ft_strlen(line_metadata->line) == 2 && !ft_strncmp(line_metadata->line, "\r\n", 2)))
			{
				line_metadata->line = get_next_line(parser->fd);
				parser->num_line += 1;
				continue ;
			}
		if (line_metadata->start_identifier_str != NULL)
			free(line_metadata->start_identifier_str);
		line_metadata->start_identifier_str = ft_strtrim(line_metadata->line, " \t");
		line_metadata->end_identifier_str = ft_strchr(line_metadata->start_identifier_str, ' ');
		if (line_metadata != NULL 
				&& ft_strchr(line_metadata->end_identifier_str, '\t') != NULL 
				&& ft_strchr(line_metadata->end_identifier_str, '\t') < line_metadata->end_identifier_str)
			line_metadata->end_identifier_str = ft_strchr(line_metadata->end_identifier_str, '\t');
		if (line_metadata->end_identifier_str)
			line_metadata->end_identifier_str = &line_metadata->start_identifier_str[ft_strlen(line_metadata->start_identifier_str) - 1];
		return ;
	}
	return ;
}

void	clean_parser_struct(t_parser *parser)
{
	if (parser->pathname_textures[NORTH] != NULL)
		free(parser->pathname_textures[NORTH]);
	if (parser->pathname_textures[SOUTH] != NULL)
		free(parser->pathname_textures[SOUTH]);
	if (parser->pathname_textures[WEST] != NULL)
		free(parser->pathname_textures[WEST]);
	if (parser->pathname_textures[EAST] != NULL)
		free(parser->pathname_textures[EAST]);
	if (parser->pathname != NULL)
		free(parser->pathname);
	if (parser->fd != -1)
		close(parser->fd);
}

void	clean_line_metadata_struct(t_line_meta *metadata)
{
	if (metadata->line != NULL)
		free(metadata->line);
	if (metadata->start_identifier_str != NULL)
		free(metadata->start_identifier_str);
	if (metadata->rgb_matrix != NULL)
		ft_delcmtrx(metadata->rgb_matrix);
}

void	err_msg_get_map_info(t_parser *parser, t_line_meta *metadata)
{
	char	*num_line_str;

	num_line_str = ft_itoa(parser->num_line);
	if (parser->error == E_OK)
		return ;
	else if (parser->error == E_IDENT_DUP)
	{
		error_handler(ERROR_MSG, "duplicated identifier: line ", num_line_str, ": ");
		error_handler(RED, metadata->start_identifier_str, RESET, "\n");
	}
	else if (parser->error == E_IDENT_INV)
	{
		error_handler(ERROR_MSG, "invalid identifier: line ", num_line_str, ": ");
		error_handler(RED, metadata->start_identifier_str, RESET, "\n");
	}
	free(num_line_str);
	clean_parser_struct(parser);
	clean_line_metadata_struct(metadata);
	exit (EXIT_FAILURE);
}

int	identify_identifier(t_parser *parser, t_line_meta *metadata)
{
	int	lenght_identifier;

	lenght_identifier = metadata->end_identifier_str - metadata->start_identifier_str;
	if (!ft_strncmp(metadata->start_identifier_str, "NO", lenght_identifier))
		set_texture_pathname(parser, metadata, NORTH, lenght_identifier);
	else if (!ft_strncmp(metadata->start_identifier_str, "SO", lenght_identifier))
		set_texture_pathname(parser, metadata, SOUTH, lenght_identifier);
	else if (!ft_strncmp(metadata->start_identifier_str, "WE", lenght_identifier))
		set_texture_pathname(parser, metadata, WEST, lenght_identifier);
	else if (!ft_strncmp(metadata->start_identifier_str, "EA", lenght_identifier))
		set_texture_pathname(parser, metadata, EAST, lenght_identifier);
	else if (!ft_strncmp(metadata->start_identifier_str, "C", lenght_identifier))
		validating_rgb(parser, metadata);
	else if (!ft_strncmp(metadata->start_identifier_str, "F", lenght_identifier))
		validating_rgb(parser, metadata);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	set_texture_pathname(t_parser *parser, t_line_meta *metadata, t_texture_index identifier, int lenght_identifier)
{
	if (parser->pathname_textures[identifier] == NULL)
		parser->pathname_textures[identifier] = ft_strtrim(&metadata->start_identifier_str[lenght_identifier], " \t");
	else
		parser->error = E_IDENT_DUP;
	err_msg_get_map_info(parser, metadata);
	return ;
}

void	get_map_info(t_parser *parser)
{
	t_line_meta	metadata_line;

	ft_bzero(&metadata_line, sizeof(t_line_meta));
	while (true)
	{
		validating_line(parser, &metadata_line);
		if (metadata_line.line != NULL)
		{
			if (identify_identifier(parser, &metadata_line))
				parser->error = E_IDENT_INV;
			err_msg_get_map_info(parser, &metadata_line);
		}
		else
			break ;
	}
}

t_data	*parse(int argc, char **argv)
{
	t_parser parser;
	t_data	*data;
	t_plr	*coord;

	ft_bzero(&parser, sizeof(parser));
	validating_arguments(&parser, argc, argv);
	validating_file(&parser);
	get_map_info(&parser);
	data = ft_calloc(1, sizeof(t_data));
	init_data(data);
	coord = ft_calloc(1, sizeof(t_plr));
	init_coord(coord, data);
	return (data);
}

static int	init_data(t_data *data)
{
	data->window.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (data->window.mlx == NULL)
		return (ft_putendl_fd((char *) mlx_strerror(mlx_errno), STDERR_FILENO), EXIT_FAILURE);
	data->window.image = mlx_new_image(data->window.mlx, WIDTH, HEIGHT);
	if (data->window.image == NULL)
		return (ft_putendl_fd((char *) mlx_strerror(mlx_errno), STDERR_FILENO), EXIT_FAILURE);
	return (0);
}

// static char **cpy_file(char *file)
// {
// 	int		fd;
// 	int		i;
// 	char	**cpy;
// 	char	*str;

// 	cpy = NULL;
// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 		return (NULL);
// 	i = 0;
// 	while ((str = get_next_line(fd)))
// 	{
// 		free(str);
// 		i++;
// 	}
// 	cpy = malloc(sizeof(char *) * (i + 1));
// 	close(fd);
// 	fd = open(file, O_RDONLY);
// 	i = 0;
// 	while ((str = get_next_line(fd)))
// 	{
// 		cpy[i] = str;
// 		i++;
// 	}
// 	cpy[i] = NULL;
// 	close(fd);
// 	return (cpy);
// }

static void	init_coord(t_plr *coord, t_data *data)
{
	coord->pos[X] = 12.5;
	coord->pos[Y] = 22.5;
	coord->dir[Y] = 0;
	coord->dir[X] = -1;
	coord->plane[Y] = (coord->dir[X] * sin(M_PI_2) + coord->dir[Y] * cos(M_PI_2)) * 0.66;
	coord->plane[X] = (coord->dir[X] * cos(M_PI_2) + coord->dir[Y] * -sin(M_PI_2)) * 0.66;
	// coord->time[CURRENT] = 0;
	// coord->time[OLD_TIME] = 0;
	data->coord = coord;
}
