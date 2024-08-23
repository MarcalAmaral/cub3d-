/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.error.identifiers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:49:29 by myokogaw          #+#    #+#             */
/*   Updated: 2024/08/22 13:49:29 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "data.h"
#include "parse.h"
#include "cleaner/clear.h"
#include "defines.h"

void	format_identifier_error(t_parser *parser)
{
	char	*num_line_str;

	if (parser->error == E_OK)
		return ;
	num_line_str = ft_itoa(parser->num_line);
	if (parser->error == E_IDENT_DUP)
		display_error(ERROR_MSG, " duplicated identifier: line ", num_line_str, ": ");
	else if (parser->error == E_IDENT_INV)
		display_error(ERROR_MSG, " invalid identifier: line ", num_line_str, ": ");
	else if (parser->error == E_IDENT_EMPTY_CONTENT)
		display_error(ERROR_MSG, " not accept empty content: line ", num_line_str, ": ");
	display_error(RED, parser->meta.start_id_str, RESET, "\n");
	free(num_line_str);
	clean_parser_struct(parser);
	exit (EXIT_FAILURE);
}
