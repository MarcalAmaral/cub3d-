/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:57:59 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/21 15:40:19 by myokogaw         ###   ########.fr       */
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
	E_IDENT_INV,
	E_IDENT_DUP,
	E_RGB_INVAMOUNT,
	E_RGB_DIGIT,
	E_RGB_INVRANGE
};

typedef struct s_line_meta {
	char					*line;
	char					*start_identifier_str;
	char					*end_identifier_str;
	char					**rgb_matrix;
	int						rgb_matrix_index;
	int						rgb_char_index;
}	t_line_meta;

typedef	struct s_parser {
	char					*pathname_textures[4];
	int						*rgb_array[2];
	char					*pathname;
	int						num_line;
	int						fd;
	enum e_parser_errors	error;
}	t_parser;

t_data	*parse(int argc, char **argv);

#endif