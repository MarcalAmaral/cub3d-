/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg_arguments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:30:09 by myokogaw          #+#    #+#             */
/*   Updated: 2024/08/22 13:30:09 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "data.h"
#include "defines.h"
#include "utils.h"
#include "parse.h"
#include "cleaner/clear.h"

void	format_arg_error(t_parser *parser, char *pathname)
{
	if (parser->error == E_OK)
		return ;
	else if (parser->error == E_ARG_INVNUM)
		display_error(ERROR_MSG, " Invalid number of arguments <./cub3d \"path_to_file.cub\">\n", NULL, NULL);
	else if (parser->error == E_ARG_INVEXT)
	{
		display_error(ERROR_MSG,
			" Invalid path, path with .cub extension required: ", RED, pathname);
		display_error(RESET, "\n", NULL, NULL);
	}
	exit (EXIT_FAILURE);
}

void	format_file_error(t_parser *parser)
{
	if (parser->error == E_OK)
		return ;
	else if (parser->error == E_FILE_ISDIR)
		display_error(ERROR_MSG, " ", strerror(EISDIR), ": ");
	else if (parser->error == E_FILE_FAILOPEN)
		display_error(ERROR_MSG, " ", strerror(errno), ": ");
	else if (parser->error == E_FILE_EMPTY)
		display_error(ERROR_MSG, " empty file: ", NULL, NULL);
	display_error(RED, parser->pathname, RESET, "\n");
	clean_parser_struct(parser);
	exit (EXIT_FAILURE);
}
