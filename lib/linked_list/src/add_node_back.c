/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:13:20 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/10 14:34:13 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static void	ft_first_matrix_node(t_lst *lst, t_node *node);
static void	ft_second_matrix_node(t_lst *lst, t_node *node);
static void	ft_third_onwards_matrix_node(t_lst *lst, t_node *node);

int	ft_add_node_back(t_lst *lst, t_node *node)
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
	node->next = lst->head;
	node->prev = lst->head;
	lst->head->next = node;
	lst->head->prev = node;
	lst->last = node;
	lst->size++;
}

static void	ft_third_onwards_matrix_node(t_lst *lst, t_node *node)
{
	t_var	var;

	var.last = lst->last;
	node->prev = var.last;
	node->next = lst->head;
	lst->head->prev = node;
	var.last->next = node;
	lst->last = node;
	lst->size++;
}
