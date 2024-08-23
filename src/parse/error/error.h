/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:31:08 by myokogaw          #+#    #+#             */
/*   Updated: 2024/08/22 13:31:08 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_PARSE_H
# define ERROR_PARSE_H

void	format_arg_error(t_parser *parser, char *pathname);
void	format_rgb_error(t_parser *parser);
void	format_file_error(t_parser *parser);
void	format_identifier_error(t_parser *parser);
void    format_memalloc_error(t_parser *parser);

#endif