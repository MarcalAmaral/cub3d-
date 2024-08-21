/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:17:10 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/10 14:34:13 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static void	ft_first_matrix_node(t_lst *lst, t_node *node);
static void	ft_second_matrix_node(t_lst *lst, t_node *node);
static void	ft_third_onwards_matrix_node(t_lst *lst, t_node *node);

int	ft_add_node_front(t_lst *lst, t_node *node)
{
	if (!lst)
		return (-1);
	if (lst->size == 0)
	{
		ft_first_matrix_node(lst, node);
		return (0);
	}
	else if (lst->size == 1)
	{
		ft_second_matrix_node(lst, node);
		return (0);
	}
	else
	{
		ft_third_onwards_matrix_node(lst, node);
		return (0);
	}
}

static void	ft_first_matrix_node(t_lst *lst, t_node *node)
{
	node->next = node;
	node->prev = node;
	lst->head = node;
	lst->last = node;
	lst->size = 1;
}

static void	ft_second_matrix_node(t_lst *lst, t_node *node)
{
	node->next = lst->last;
	node->prev = lst->last;
	lst->last->prev = node;
	lst->last->next = node;
	lst->head = node;
	lst->size++;
}

static void	ft_third_onwards_matrix_node(t_lst *lst, t_node *node)
{
	t_var	var;

	var.head = lst->head;
	var.head = lst->head;
	node->next = var.head;
	node->prev = lst->last;
	lst->last->next = node;
	var.head->prev = node;
	lst->head = node;
	lst->size++;
}
