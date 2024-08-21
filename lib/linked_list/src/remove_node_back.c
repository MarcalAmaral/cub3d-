/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_node_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:16:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/27 12:56:55 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static int	ft_one_node(t_lst *lst);
static int	ft_two_node(t_lst *lst);
static int	ft_three_more(t_lst *lst);

int	lst_rmv_back(t_lst *lst)
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

	var.last = lst->last;
	lst->last = NULL;
	lst->head = NULL;
	lst->size = 0;
	free(var.last);
	var.last = NULL;
	return (0);
}

static int	ft_two_node(t_lst *lst)
{
	t_var	var;

	var.last = lst->last;
	lst->head->next = lst->head;
	lst->head->prev = lst->head;
	lst->last = lst->head;
	lst->size--;
	free (var.last);
	var.last = NULL;
	return (0);
}

static int	ft_three_more(t_lst *lst)
{
	t_var	var;

	var.last = lst->last;
	var.second_last = var.last->prev;
	var.second_last->next = lst->head;
	lst->head->prev = var.second_last;
	lst->last = var.second_last;
	lst->size--;
	free(var.last);
	var.last = NULL;
	return (0);
}
