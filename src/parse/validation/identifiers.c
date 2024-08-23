/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.validations.identifiers.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:58:37 by myokogaw          #+#    #+#             */
/*   Updated: 2024/08/22 13:58:37 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "data.h"
#include "libft.h"
#include "parse.h"
#include "error/error.h"

int		check_rgb_id_dup(t_parser *parser)
{
	if (*parser->meta.start_id_str == 'C' && parser->ceiling_rgb[3] == 1)
		parser->error = E_IDENT_DUP;
	else if (*parser->meta.start_id_str == 'F' && parser->floor_rgb[3] == 1)
		parser->error = E_IDENT_DUP;
	format_identifier_error(parser);
	return (EXIT_SUCCESS);
}

void	check_tex_id_dup(t_parser *parser, t_texture_index id, int len_id)
{
	if (parser->pathname_textures[id] == NULL)
		parser->pathname_textures[id] = ft_strtrim(&parser->meta.start_id_str[len_id], " \t\r\n");
	else
		parser->error = E_IDENT_DUP;
	format_identifier_error(parser);
	return ;
}