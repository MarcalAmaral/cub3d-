/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_add_back_lst.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:12:36 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 10:01:18 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static void	ft_first_matrix_node(t_lst *lst, t_node *new_node);
static void	ft_second_matrix_node(t_lst *lst, t_node *new_node);
static void	ft_third_onwards_matrix_node(t_lst *lst, t_node *new_node);

int	ft_create_node_add_back(t_lst *lst, char content)
{
	t_node	*new_node;

	if (!lst)
		return (-1);
	new_node = ft_init_node(content);
	if (!new_node)
		return (-1);
	if (lst->size == 0)
	{
		ft_first_matrix_node(lst, new_node);
		return (0);
	}
	else if (lst->size == 1)
	{
		ft_second_matrix_node(lst, new_node);
		return (0);
	}
	else
	{
		ft_third_onwards_matrix_node(lst, new_node);
		return (0);
	}
}

static void	ft_first_matrix_node(t_lst *lst, t_node *new_node)
{
	new_node->next = new_node;
	new_node->prev = new_node;
	lst->head = new_node;
	lst->last = new_node;
	lst->size = 1;
}

static void	ft_second_matrix_node(t_lst *lst, t_node *new_node)
{
	new_node->next = lst->head;
	new_node->prev = lst->head;
	lst->head->next = new_node;
	lst->head->prev = new_node;
	lst->last = new_node;
	lst->size++;
}

static void	ft_third_onwards_matrix_node(t_lst *lst, t_node *new_node)
{
	t_var	var;

	var.last = lst->last;
	new_node->prev = var.last;
	new_node->next = lst->head;
	lst->head->prev = new_node;
	var.last->next = new_node;
	lst->last = new_node;
	lst->size++;
}
