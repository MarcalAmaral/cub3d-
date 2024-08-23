/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.error.rgb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:40:51 by myokogaw          #+#    #+#             */
/*   Updated: 2024/08/22 13:40:51 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "data.h"
#include "parse.h"
#include "cleaner/clear.h"
#include "utils.h"
#include "libft.h"
#include "defines.h"

static void multiple_values(t_parser *parser)
{
	int	it;

	ft_putstr_fd(parser->meta.cur_id, STDERR_FILENO);
	ft_putstr_fd(" ", STDERR_FILENO);
	it = -1;
	while (parser->meta.rgb_matrix[++it])
	{
		if (parser->meta.rgb_matrix[it + 1] != NULL)
			display_error(RED, parser->meta.rgb_matrix[it], RESET, ",");
		else if (parser->meta.rgb_matrix[it + 1] == NULL)
			display_error(RED, parser->meta.rgb_matrix[it], RESET, "\n");
	}
}

static void display_rgb_wrong_value(t_parser *parser)
{
	int	it;
	int	w_val;

	if (parser->error == E_RGB_INVAMOUNT)
	{
		multiple_values(parser);
		return ;
	}
	w_val = parser->meta.rgb_str_index;
	it = -1;
	ft_putstr_fd(parser->meta.cur_id, STDERR_FILENO);
	ft_putstr_fd(" ", STDERR_FILENO);
	while (parser->meta.rgb_matrix[++it])
	{
		if (it != w_val && parser->meta.rgb_matrix[it + 1] != NULL)
			display_error(parser->meta.rgb_matrix[it], ",", NULL, NULL);
		else if (it != w_val && parser->meta.rgb_matrix[it + 1] == NULL)
			display_error(parser->meta.rgb_matrix[it], "\n", NULL, NULL);
		else if (it == w_val && parser->meta.rgb_matrix[it + 1] != NULL)
			display_error(RED, parser->meta.rgb_matrix[it], RESET, ",");
		else if (it == w_val && parser->meta.rgb_matrix[it + 1] == NULL)
			display_error(RED, parser->meta.rgb_matrix[it], RESET, "\n");
	}
}


void	format_rgb_error(t_parser *parser)
{
	char	*num_line_str;

	if (parser->error == E_OK)
		return ;
	num_line_str = ft_itoa(parser->num_line);
	if (parser->error == E_RGB_INVAMOUNT)
		display_error(ERROR_MSG,
			" invalid quantity of elements to represent an RGB value: line ",
			num_line_str, ": ");
	else if (parser->error == E_RGB_DIGIT)
		display_error(ERROR_MSG,
			" just digits is needed to represent RGB colors: line ",
			num_line_str, ": ");
	else if (parser->error == E_RGB_INVRANGE)
		display_error(ERROR_MSG,
			" invalid range for rgb values, needed 0 <= value >= 255: line ",
			num_line_str, ": ");
	display_rgb_wrong_value(parser);
	clean_parser_struct(parser);
	free(num_line_str);
	exit (EXIT_FAILURE);
}
