/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:49:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/20 23:58:30 by myokogaw         ###   ########.fr       */
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


// Validações para serem realizadas:
// 	Primeira validação: Argumentos recebidos (int argc, char **av)
// 		Validar quantidade de argumentos recebidos, o programa recebe no máximo dois e no mínimo dois argumentos
// 		Validar se o argumento recebido possui extensão .cub
//		Validar se o filename passado não é um diretório e se é possível abrir para ler o arquivo
// 	Segunda validação: Validar as informações do arquivo .cub fornecido
// 		Validar se o arquivo contempla todas as informações necessárias
// 		Validar se não há valores repetidos tanto para os identificadores e os valores do RGB dos identificadores C e F
// 		Validar se possui uma textura diferente para cada direção cardial
//		Validar se os identificadores das texturas são NO, SO, WE, EA
// 		Validar se as cores rgb dos identificadores C e F estão formatadas corretamente
// 		Validar se o mapa é composto somente por 1 e 0 e o player (NSWE)
// 		Validar se o mapa no qual o player (NSWE) se encontra está fechado por paredes
		

static int	init_data(t_data *data);
// static char **cpy_file(char *file);
static void	init_coord(t_plr *coord, t_data *data);

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
	else if (ft_strnstr(&(av[1][ft_strlen(av[1]) - 4]), ".cub", 4) == NULL)
		parser->error = E_ARG_INVEXT;
	error_arguments(parser);
	parser->pathname = ft_strdup(av[1]);
}

void	error_file(t_parser *parser)
{W
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

int	err_msg_values_of_rgb(char **rgb_colors, char *identifier, int matrix_index, t_error_value_rgb *error_struct)
{
	char	*line_err;
	int		iterator;
	int		matrix_lenght;

	line_err = ft_itoa(error_struct->file_line);
	if (error_struct->error_rgb == E_RGB_DIGIT)
		error_handler("\033[31mError\033[39m\n just digits is needed for especify colors: line ", line_err, ": ", identifier);
	else if (error_struct->error_rgb == E_RGB_MAXRANGE)
		error_handler("\033[31mError\033[39m\n Invalid rgb color max 3 digits: line ", line_err, ": ", identifier);
	ft_putstr_fd(" ", STDERR_FILENO);
	matrix_lenght = ft_mtrxlen(rgb_colors);
	iterator = 0;
	while (iterator < matrix_lenght)
	{
		if (iterator == matrix_index)
		{
			if (iterator == matrix_lenght - 1)
				error_handler("\033[31m", rgb_colors[iterator], "\033[39m", NULL);
			else
				error_handler("\033[31m", rgb_colors[iterator], "\033[39m", ",");
			iterator++;
			continue ;
		}
		if (iterator != matrix_lenght - 1)
			error_handler(rgb_colors[iterator], ",", NULL, NULL);
		else
			error_handler(rgb_colors[iterator], NULL, NULL, NULL);
		iterator++;
	}
	free(line_err);
	return (EXIT_FAILURE);
}

int	validating_values_of_rgb(t_parser *parser, t_metadata *metadata)
{
	int	matrix_index;
	int	char_index;

	matrix_index = -1;
	while (metadata->rgb_matrix[++matrix_index])
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
			parser->error = E_RGB_MAXRANGE;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	validating_rgb_pattern(t_parser *parser, t_metadata *metadata)
{
	int	condition_met;

	condition_met = 0;
	if (ft_mtrxlen(rgb_matrix) != 3)
	{
		parser->error = E_RGB_INVAMOUNT;
		condition_met = 1;
	}
	else if (!condition_met && validating_values_of_rgb(parser, metadata))
		condition_met = 1;
	err_msg_rgb(parser, metadata);
}

int	validating_rgb(t_parser *parser, t_line_metadata *metadata)
{
	char	**rgb_matrix;
	char	*rgb_string;

	rgb_setup_string = ft_strtrim(&metadata->end_identifier_str, " \t");
	metadata->rgb_matrix = ft_split(rgb_string, ',');
	free(rgb_string);
	if (metadata->rgb_matrix == NULL)
		return (EXIT_FAILURE);
	validating_rgb_pattern(parser, metadata);

	if (validating_values_of_rgb(rgb_colors, identifier, line_count))
	{
		free(colors);
		ft_delcmtrx(rgb_colors);
		return (EXIT_FAILURE);
	}
	matrix_index = -1;
	while(rgb_colors[++matrix_index])
	{
		color_value = ft_atoi(rgb_colors[matrix_index]);
		if (color_value > 255)
		{
			ft_putendl_fd("Error\n Invalid rgb range color", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		else if (color_value < 0)
		{
			ft_putendl_fd("Error\n Invalid rgb range color", STDERR_FILENO);
			return (EXIT_FAILURE);
		}

	}
	return (EXIT_SUCCESS);
}

void	validating_line(t_parser *parser, t_line_meta *line_metadata)
{
	line_metadata->line = get_next_line(parser->fd);
	parser->num_line += 1;
	while (line_metadata->line)
	{
		if ((ft_strlen(line_metadata->line) == 1 && ft_strncmp(line_metadata->line, "\n"))
			|| (ft_strlen(line_metadata->line) == 2 && ft_strncmp(line_metadata->line, "\r\n")))
			{
				line_metadata->line = get_next_line(parser->fd);
				parser->num_line += 1;
			}
		if (line_metadata->start_identifier != NULL)
			free(line_metadata->start_identifier);
		line_metadata->start_identifier_str = ft_strtrim(line_metadata->line, " \t");
		line_metadata->end_indentifier_str = ft_strchr(line_metadata->start_identifier->str, " ");
		if (ft_strchr(line_metadata->end_identifier_str, "\t") < line_metadata->end_identifier_str)
			line_metadata->end_identifier = ft_strchr(line_metadata->end_identifier_str, "\t");
		return ;
	}
	return ;
}

void	clean_parser_struct(t_parser *parser)
{
	if (parser->pathname_struct[NORTH] != NULL)
		free(parser->pathname_struct[NORTH]);
	if (parser->pathname_struct[SOUTH] != NULL)
		free(parser->pathname_struct[SOUTH]);
	if (parser->pathname_struct[WEST] != NULL)
		free(parser->pathname_struct[WEST]);
	if (parser->pathname_struct[EAST] != NULL)
		free(parser->pathname_struct[EAST]);
	if (parser->pathname != NULL)
		free(parser->pathname);
	if (parser->fd != -1)
		close(parser->fd);
}

void	clean_line_metadata_struct(t_line_metadata *metadata)
{
	if (metadata->line != NULL)
		free(metadata->line);
	if (metadata->start_identifier_str != NULL);
		free(metadata->start_identifier_str);
	if (metadata->rgb_matrix != NULL)
		ft_delcmtrx(metadata->rgb_matrix);
}

void	err_msg_get_map_info(t_parser *parser, t_line_metadata *metadata)
{
	char	*num_line_str;

	num_line_str = NULL;
	if (parser->error == E_OK)
		return ;
	else if (parser->error == E_IDENT_DUP)
	{
		num_line_str = ft_itoa(parser->num_line);
		error_handler(ERROR_MSG, "duplicated identifier: line ", num_line_str, ": ");
		error_handler(RED, metadata->start_identifier_line, RESET, "\n");
	}
	else if (parser->error == E_IDENT_INV)
	{
		num_line_str = ft_itoa(parser->num_line);
		error_handler(ERROR_MSG, "invalid identifier: line ", num_line_str, ": ");
		error_handler(RED, metadata->start_identifier_line, RESET, "\n");
	}
	if (num_line_str != NULL)
		free(num_line_str);
	clean_parser_struct(parser);
	clean_line_metadata_struct(metadata);
	exit (EXIT_FAILURE);
}

int	set_texture_pathname(t_parser *parser, t_line_meta *metadata, t_texture_index identifier, int lenght_identifier)
{
	if (parser->pathname_textures[identifier] == NULL)
		parser->pathname_textures[identifier] = ft_strtrim(&metadata->start_identifier_str[lenght_identifier], " \t");
	else
		parser->error = E_IDENT_DUP;
	err_msg_get_map_info(parser, metadata);
	return ;
}

int	get_map_info(t_parser *parser)
{
	t_line_meta	metadata_line;
	int			lenght_identifier;

	ft_bzero(&metadata_line, sizeof(t_line_meta));
	while (true)
	{
		validating_line(parser, &metadata_line);
		lenght_identifier = metadata_line.end_identifier_str - metadata_line.start_identifier_str;
		if (metadata_line->line != NULL && lenght_identifier <= 2)
		{
			if (lenght_identifier == 2)
			{
				if (!ft_strncmp(start_identifier_str, "NO", lenght_identifier))
					set_texture_pathname(parser, metadata_line, NORTH, lenght_identifier);
				else if (!ft_strncmp(start_identifier_str, "SO", lenght_identifier))
					set_texture_pathname(parser, metadata_line, SOUTH, lenght_identifier);
				else if (!ft_strncmp(start_identifier_str, "WE", lenght_identifier))
					set_texture_pathname(parser, metadata_line, WEST, lenght_identifier);
				else if (!ft_strncmp(start_identifier_str, "EA", lenght_identifier))
					set_texture_pathname(parser, metadata_line, EAST, lenght_identifier);
			}
			else if (lenght_identifier == 1)
			{
				if (!ft_strncmp(start_identifier_str, "C", lenght_identifier))
				{
					if (validating_rgb(parser, metadata))
					{
						free(content);
						free(start_identifier_str);
						close(fd);
						return (EXIT_FAILURE);
					}
				}
				else if (!ft_strncmp(start_identifier_str, "F", lenght_identifier))
				{
					if (validating_rgb(parser, metadata))
					{
						free(content);
						free(start_identifier_str);
						close(fd);
						return (EXIT_FAILURE);
					}
				}
			}
			else
				parser->error = E_IDENT_INV;
			err_msg_get_map_info(parser, &metadata);
		}
		else
			break ;
	}
	return (EXIT_SUCCESS);
}

t_data	*parse(int argc, char **argv)
{
	t_parser parser;
	t_data	*data;
	t_plr	*coord;
	int		fd;

	ft_bzero(&parser, sizeof(parser));
	validating_arguments(&parser, argc, argv);
	validating_file(&parser, av[1]);
	if (get_map_info(data, fd))
	{
		free(data);
		return (NULL);
	}
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
