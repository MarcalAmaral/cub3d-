/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.validations.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:52:06 by myokogaw          #+#    #+#             */
/*   Updated: 2024/08/22 13:52:06 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_VALIDATIONS_H
# define PARSE_VALIDATIONS_H

int     validating_rgb(t_parser *parser);
int		check_rgb_id_dup(t_parser *parser);
void	check_tex_id_dup(t_parser *parser, t_texture_index id, int len_id);
void	check_file(t_parser *parser);
void	check_arguments(t_parser *parser, int ac, char **av);

#endif