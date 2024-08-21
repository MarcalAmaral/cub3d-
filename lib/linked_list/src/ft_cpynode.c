/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpynode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:38:33 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/01 12:59:27 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

t_node	*ft_cpynode(t_node *node_origin)
{
	t_node	*new_node;

	if (!node_origin)
		return (NULL);
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->c = node_origin->c;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
