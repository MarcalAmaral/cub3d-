/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memalloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:54:27 by myokogaw          #+#    #+#             */
/*   Updated: 2024/08/22 15:54:27 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "data.h"
#include "parse.h"
#include "cleaner/clear.h"
#include "defines.h"
#include "utils.h"

void    format_memalloc_error(t_parser *parser)
{
    if (parser->error == E_OK)
        return ;
    if (parser->error == E_MEM_RGB_MATRIX)
        display_error(ERROR_MSG, " error allocating memory for rgb matrix\n", NULL, NULL);
    else if (parser->error == E_MEM_RGB_STRING)
        display_error(ERROR_MSG, " error allocating memory for rgb string\n", NULL, NULL);
    exit (EXIT_FAILURE);
}