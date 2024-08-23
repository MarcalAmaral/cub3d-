/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:36:55 by myokogaw          #+#    #+#             */
/*   Updated: 2024/08/22 13:36:55 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "data.h"
#include "parse.h"
#include "libft.h"

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
	if (parser->meta.content_id_str != NULL)
		free(parser->meta.content_id_str);
	if (parser->pathname != NULL)
		free(parser->pathname);
	if (parser->fd != -1)
		close(parser->fd);
	if (parser->meta.line != NULL)
		free(parser->meta.line);
	if (parser->meta.start_id_str != NULL)
		free(parser->meta.start_id_str);
	if (parser->meta.rgb_matrix != NULL)
		ft_delcmtrx(parser->meta.rgb_matrix);
}
