/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:57:59 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/22 22:34:52 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

enum e_identifiers {
	CEILING,
	FLOOR
};

enum e_parser_errors {
	E_OK,
	E_ARG_INVNUM,
	E_ARG_INVEXT,
	E_FILE_ISDIR,
	E_FILE_FAILOPEN,
	E_FILE_EMPTY,
	E_IDENT_INV,
	E_IDENT_DUP,
	E_IDENT_EMPTY_CONTENT,
	E_RGB_INVAMOUNT,
	E_RGB_DIGIT,
	E_RGB_INVRANGE,
	E_MEM_RGB_MATRIX,
	E_MEM_RGB_STRING,
	E_MAP_EMPTY_LINE,
	E_MAP_INV_ELEM
};

typedef struct s_parser_metadata {
	char					cur_id[3];
	char					*line;
	char					*start_id_str;
	char					*end_id_str;
	char					*content_id_str;
	char					**rgb_matrix;
	int						start_map_content;
	int						str_index;
	int						c_index;
}	t_parser_metadata;

typedef	struct s_parser {
	t_parser_metadata		meta;
	enum e_parser_errors	error;
	char					*pathname_textures[4];
	int						ceiling_rgb[4];
	int						floor_rgb[4];
	char					*pathname;
	int						num_line;
	int						fd;
}	t_parser;

t_data	*parse(int argc, char **argv);

#endif