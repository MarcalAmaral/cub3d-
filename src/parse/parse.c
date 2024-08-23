/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:49:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/22 22:37:24 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
#include "data.h"
#include "parse.h"
#include "error/error.h"
#include "validation/validations.h"


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
// void		set_texture_pathname(t_parser *parser, t_line_meta *metadata, t_texture_index identifier, int len_id);


void	check_empty_file(t_parser *parser)
{
	parser->meta.line = get_next_line(parser->fd);
	parser->num_line += 1;
	if (parser->meta.line == NULL)
		parser->error = E_FILE_EMPTY;
	format_file_error(parser);
	return ;
}

int	ft_char_map(char c)
{
	if (c == '0' || c == '1' || c == 'N'
		|| c == 'W' || c == 'E' || c == 'S')
		return (true);
	return (false);
}

int	is_map_line(t_parser *parser)
{
	int		char_index;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(parser->meta.line, " \n\r\t");
	free(parser->meta.line);
	parser->meta.line = trimmed_line;
	char_index = 0;
	while (ft_char_map(parser->meta.line[char_index]))
		char_index++;
	if (parser->meta.line[char_index] == '\0')
		return (true);
	parser->meta.c_index = char_index;
	return (false);
}


int	all_filled(t_parser *parser)
{
	if (parser->ceiling_rgb[3] == true && parser->floor_rgb[3] == true
		&& parser->pathname_textures[NORTH] != NULL
		&& parser->pathname_textures[SOUTH] != NULL
		&& parser->pathname_textures[WEST] != NULL
		&& parser->pathname_textures[EAST] != NULL)
		return (true);
	return (false);
}

void	display_invalid_elem(t_parser *parser)
{
	char	s_temp[2];
	int		bytes_printed;

	if (!parser->error == E_MAP_EMPTY_LINE)
		return ;
	ft_strlcpy(s_temp, &parser->meta.line[parser->meta.c_index], 2);
	parser->meta.line[parser->meta.c_index] = 0;
	bytes_printed = write(STDERR_FILENO, parser->meta.line, ft_strlen(parser->meta.line));
	display_error(RED, s_temp, RESET, NULL);
	display_error(&parser->meta.line[bytes_printed], "\n", NULL, NULL);
	parser->meta.line[parser->meta.c_index] = s_temp[0];
}

void	format_map_error(t_parser *parser)
{
	char *num_line_str;
	
	if (parser->error == E_OK)
		return ;
	num_line_str = ft_itoa(parser->num_line);
	if (parser->error == E_MAP_EMPTY_LINE)
		display_error(ERROR_MSG, " invalid map, empty line on map: line ", num_line_str, ": \n");
	else if (parser->error == E_MAP_INV_ELEM)
		display_error(ERROR_MSG, " invalid map, an invalid elem in map: line ", num_line_str, ": ")
	display_invalid_elem(parser);
	clean_parser_struct(parser);
	exit (EXIT_FAILURE);
}

int	check_line(t_parser *parser)
{
	char *line;

	line = parser->meta.line;
	if (parser->meta.start_map_content == true)
	{
		if ((ft_strlen(line) == 1 && !ft_strncmp(line, "\n", 1))
			|| (ft_strlen(line) == 2 && !ft_strncmp(line, "\r\n", 2)))
			parser->error = E_MAP_EMPTY_LINE;
		if (is_map_line(parser))
			parser->error = E_MAP_INV_ELEM;
		format_map_error(parser);
		return ;
	}
	if ((ft_strlen(line) == 1 && !ft_strncmp(line, "\n", 1))
		|| (ft_strlen(line) == 2 && !ft_strncmp(line, "\r\n", 2)))
	{
		free(line);
		return (EXIT_FAILURE);
	}
	if (parser->meta.start_map_content == false
		&& is_map_line(parser) && all_filled(parser))
		parser->meta.start_map_content = true;
	return (EXIT_SUCCESS);
}

void	get_valid_line(t_parser *parser)
{
	if (parser->meta.line != NULL && parser->num_line != 1)
	{
		free(parser->meta.line);
		parser->meta.line = get_next_line(parser->fd);
		parser->num_line += 1;
	}
	while (parser->meta.line)
	{
		// printf("file line %d\n", parser->num_line);
		if (!check_line(parser))
			return ;
		// if (parser->start_map_content == true)
		// 	check_empty_line_on_map(parser);
		parser->meta.line = get_next_line(parser->fd);
		parser->num_line += 1;
	}
	return ;
}

void	set_start_end_id_str(t_parser *parser)
{
	if (parser->meta.start_id_str != NULL)
		free(parser->meta.start_id_str);
	parser->meta.start_id_str = ft_strtrim(parser->meta.line, " \t\r\n");
	parser->meta.end_id_str = ft_strchr(parser->meta.start_id_str, ' ');
	if (parser->meta.end_id_str != NULL
			&& ft_strchr(parser->meta.end_id_str, '\t') != NULL 
			&& ft_strchr(parser->meta.end_id_str, '\t') < parser->meta.end_id_str)
		parser->meta.end_id_str = ft_strchr(parser->meta.end_id_str, '\t');
	if (!parser->meta.end_id_str)
		parser->meta.end_id_str = &parser->meta.start_id_str[ft_strlen(parser->meta.start_id_str) - 1];
}

void	check_valid_id(t_parser *parser)
{
	long int id_len;

	id_len = parser->meta.start_id_str - parser->meta.end_id_str;
	if (id_len < 1 && id_len > 2)
		parser->error = E_IDENT_INV;
	format_identifier_error(parser);
	return ;
}

void	check_empty_content(t_parser *parser)
{
	if (*parser->meta.content_id_str == '\0')
		parser->error = E_IDENT_EMPTY_CONTENT;
	format_identifier_error(parser);
	return ;
}

void	get_line_metadata(t_parser *parser)
{
	get_valid_line(parser);
	set_start_end_id_str(parser);
	check_valid_id(parser);
	if (parser->meta.content_id_str != NULL)
		free(parser->meta.content_id_str);
	parser->meta.content_id_str = ft_strtrim(parser->meta.end_id_str, " \n\r\t");
	// printf("parser->meta.content_id_str %d\n", *parser->meta.content_id_str);
	check_empty_content(parser);
	ft_strlcpy(parser->meta.cur_id, parser->meta.start_id_str, (parser->meta.end_id_str - parser->meta.start_id_str + 1));
	return ;
}

int	id_resolver(t_parser *parser)
{
	int	len_id;

	len_id = ft_strlen(parser->meta.cur_id);
	// printf("cur_id %s %d len id curr_line %d\n", parser->meta.cur_id, len_id, parser->num_line);
	if (!ft_strncmp(parser->meta.cur_id, "NO", len_id))
		check_tex_id_dup(parser, NORTH, len_id);
	else if (!ft_strncmp(parser->meta.cur_id, "SO", len_id))
		check_tex_id_dup(parser, SOUTH, len_id);
	else if (!ft_strncmp(parser->meta.cur_id, "WE", len_id))
		check_tex_id_dup(parser, WEST, len_id);
	else if (!ft_strncmp(parser->meta.cur_id, "EA", len_id))
		check_tex_id_dup(parser, EAST, len_id);
	else if (!ft_strncmp(parser->meta.cur_id, "C", len_id))
		validating_rgb(parser);
	else if (!ft_strncmp(parser->meta.cur_id, "F", len_id))
		validating_rgb(parser);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// void	check_missing_information(t_parser *parser)

void	check_map_line(t_parser *parser)
{

}

void	check_if_all_filled(t_parser *parser)
{
	if (parser->ceiling_rgb[3] == true)
}

void	get_file_info(t_parser *parser)
{
	check_empty_file(parser);
	while (true)
	{
		get_line_metadata(parser);
		if (parser->meta.line != NULL)
		{
			if (parser->start_map_content == false)
			{
				if (id_resolver(parser))
					parser->error = E_IDENT_INV;
				format_identifier_error(parser);
			}
			else if (parser->start_map_content == true)
			{

			}
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
	ft_bzero(&parser.meta, sizeof(t_parser_metadata));
	check_arguments(&parser, argc, argv);
	check_file(&parser);
	get_file_info(&parser);
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
