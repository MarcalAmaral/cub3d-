/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.validations.file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:54:12 by myokogaw          #+#    #+#             */
/*   Updated: 2024/08/22 13:54:12 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "defines.h"
#include "data.h"
#include "parse.h"
#include "error/error.h"

void	check_file(t_parser *parser)
{
	parser->fd = open(parser->pathname, O_DIRECTORY);
	if (parser->fd != FAIL)
		parser->error = E_FILE_ISDIR;
	parser->fd = open(parser->pathname, O_RDONLY);
	if (parser->fd == FAIL)
		parser->error = E_FILE_FAILOPEN;
	format_file_error(parser);
}