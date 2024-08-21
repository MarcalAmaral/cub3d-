/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_nodes_between.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:16:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/03 14:12:10 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static int	empyt_lst_dst(t_lst *lst_d, t_lst *lst_n);
static int	list_dest_size_one(t_lst *lst_d, t_lst *lst_n);
static void	list_dest_size_two_more(t_node *n_a, t_node *n_b, t_lst *lst_n);
static int	node_in_list(t_lst *lst_d, t_node *node);

int	ft_lst_btwn_lst(t_lst *lst_d, t_node *n_a, t_node *n_b, t_lst *lst_n)
{
	if (!lst_d || !lst_n)
		return (-1);
	if (lst_d == lst_n)
		return (-1);
	if (lst_d->size == 0)
		return (empyt_lst_dst(lst_d, lst_n));
	if (node_in_list(lst_d, n_a) || node_in_list(lst_d, n_a))
		return (-1);
	if (n_a->next != n_b && n_b->prev != n_a)
		return (-1);
	if (lst_d->size == 1)
		return (list_dest_size_one(lst_d, lst_n));
	if (lst_d->size >= 2)
	{
		if (n_a == n_b)
			return (-1);
		list_dest_size_two_more(n_a, n_b, lst_n);
		lst_d->size += lst_n->size;
		lst_n->size = 0;
	}
	return (-1);
}

static int	empyt_lst_dst(t_lst *lst_d, t_lst *lst_n)
{
	lst_d->head = lst_n->head;
	lst_d->last = lst_n->last;
	lst_d->size = lst_n->size;
	lst_n->size = 0;
	return (0);
}

static int	list_dest_size_one(t_lst *lst_d, t_lst *lst_n)
{
	lst_d->head->next = lst_n->head;
	lst_n->head->prev = lst_d->head;
	lst_n->last->next = lst_d->head;
	lst_d->head->prev = lst_n->last;
	lst_d->last = lst_n->last;
	lst_d->size += lst_n->size;
	lst_n->size = 0;
	return (0);
}

static void	list_dest_size_two_more(t_node *n_a, t_node *n_b, t_lst *lst_n)
{
	n_a->next = lst_n->head;
	lst_n->head->prev = n_a;
	n_b->prev = lst_n->last;
	lst_n->last->next = n_b;
}

static int	node_in_list(t_lst *lst_d, t_node *node)
{
	t_var	var;

	var.current_node = lst_d->head;
	var.i = 1;
	while (var.i <= lst_d->size)
	{
		if (var.current_node == node)
			return (0);
		var.current_node = var.current_node->next;
		var.i++;
	}
	return (-1);
}
