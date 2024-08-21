/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_specific_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:32:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/27 12:56:55 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static int	ft_other_cases(t_lst *lst, t_node *node);
static int	ft_check_in_lst(t_lst *lst, t_node *node);

int	ft_remove_specific_node(t_lst *lst, t_node *node)
{
	if (!lst)
		return (-1);
	if (!node)
		return (-1);
	if (lst->size == 0)
		return (-1);
	if (ft_check_in_lst(lst, node))
		return (-1);
	if (lst->head == node)
		return (ft_remove_node_front(lst));
	if (lst->last == node)
		return (lst_rmv_back(lst));
	if (lst->last != node || lst->head != node)
		return (ft_other_cases(lst, node));
	return (-1);
}

static int	ft_other_cases(t_lst *lst, t_node *node)
{
	t_var	v;

	if (!lst)
		return (-1);
	if (!node)
		return (-1);
	v.next_node = node->next;
	v.prev_node = node->prev;
	v.next_node->prev = v.prev_node;
	v.prev_node->next = v.next_node;
	lst->size--;
	free(node);
	node = NULL;
	return (0);
}

static int	ft_check_in_lst(t_lst *lst, t_node *node)
{
	t_var	v;

	if (!lst)
		return (-1);
	if (!node)
		return (-1);
	v.current_node = lst->head;
	v.i = 1;
	while (v.i <= lst->size)
	{
		if (v.current_node == node)
			return (0);
		v.current_node = v.current_node->next;
		v.i++;
	}
	return (-1);
}
