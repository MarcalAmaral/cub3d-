/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:54:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/01 12:58:57 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

t_node	*ft_init_node(char c)
{
	t_node	*new_node;

	if (c == '\0')
		return (NULL);
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->c = c;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
