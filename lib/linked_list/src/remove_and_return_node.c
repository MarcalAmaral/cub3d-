/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_and_return_node.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:05:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/24 15:57:20 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static t_node	*ft_size_one(t_lst *lst, t_node *node);

t_node	*ft_remove_return_node(t_lst *lst, t_node *node)
{
	t_var	var;

	if (!lst || !node)
		return (NULL);
	if (!lst->head || !lst->last || lst->size == 0)
		return (NULL);
	if (node->next == node)
		return (ft_size_one(lst, node));
	var.next_node = node->next;
	var.prev_node = node->prev;
	var.prev_node->next = var.next_node;
	var.next_node->prev = var.prev_node;
	if (node == lst->head)
		lst->head = var.next_node;
	if (node == lst->last)
		lst->last = var.prev_node;
	node->next = NULL;
	node->prev = NULL;
	lst->size--;
	return (node);
}

static t_node	*ft_size_one(t_lst *lst, t_node *node)
{
	lst->head = NULL;
	lst->last = NULL;
	node->next = NULL;
	node->prev = NULL;
	lst->size--;
	return (node);
}
