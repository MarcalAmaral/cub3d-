/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_node_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:51:10 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 10:56:58 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static int	ft_one_node(t_lst *lst);
static int	ft_two_node(t_lst *lst);
static int	ft_three_more(t_lst *lst);

int	ft_remove_node_front(t_lst *lst)
{
	if (!lst)
		return (-1);
	if (lst->size == 0)
		return (-1);
	if (lst->size == 1)
		return (ft_one_node(lst));
	if (lst->size == 2)
		return (ft_two_node(lst));
	if (lst->size > 2)
		return (ft_three_more(lst));
	return (-1);
}

static int	ft_one_node(t_lst *lst)
{
	t_var	var;

	var.head = lst->head;
	lst->head = NULL;
	lst->last = NULL;
	lst->size = 0;
	free(var.head);
	var.head = NULL;
	return (0);
}

static int	ft_two_node(t_lst *lst)
{
	t_var	var;

	var.head = lst->head;
	lst->last->next = lst->last;
	lst->last->prev = lst->last;
	lst->head = lst->last;
	lst->size--;
	free(var.head);
	var.head = NULL;
	return (0);
}

static int	ft_three_more(t_lst *lst)
{
	t_var	var;

	var.head = lst->head;
	var.second = var.head->next;
	var.second->prev = lst->last;
	lst->last->next = var.second;
	lst->head = var.second;
	lst->size--;
	free(var.head);
	var.head = NULL;
	return (0);
}
