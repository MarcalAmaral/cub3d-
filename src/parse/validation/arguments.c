/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.validations.arguments.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:51:50 by myokogaw          #+#    #+#             */
/*   Updated: 2024/08/22 13:51:50 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "parse.h"
#include "error/error.h"
#include "libft.h"

void	check_arguments(t_parser *parser, int ac, char **av)
{
	if (ac != 2)
		parser->error = E_ARG_INVNUM;
	else if (ft_strlen(av[1]) < 4 || ft_strnstr(&(av[1][ft_strlen(av[1]) - 4]), ".cub", 4) == NULL)
		parser->error = E_ARG_INVEXT;
	format_arg_error(parser, av[1]);
	parser->pathname = ft_strdup(av[1]);
}
