/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_insert_node_between.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:16:50 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/03 15:10:56 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

static int	ft_size_one(t_lst *lst, t_node *node, t_lst *new_lst);
static int	ft_case_head(t_lst *lst, t_node *node, t_lst *new_lst);
static int	ft_case_last(t_lst *lst, t_lst *new_lst);
static int	ft_others(t_lst *lst, t_node *node, t_lst *new_lst);

int	insert_node_between(t_lst *lst, t_node *node, t_lst *new_lst)
{
	if (!lst || !node || !new_lst)
		return (-1);
	if (lst->size == 0 || new_lst->size == 0)
		return (-1);
	if (lst->size == 1)
		return (ft_size_one(lst, node, new_lst));
	else if (lst->head == node)
		return (ft_case_head(lst, node, new_lst));
	else if (lst->last == node)
		return (ft_case_last(lst, new_lst));
	return (ft_others(lst, node, new_lst));
}

static int	ft_size_one(t_lst *lst, t_node *node, t_lst *new_lst)
{
	node->next = new_lst->head;
	new_lst->head->prev = node;
	node->prev = new_lst->last;
	new_lst->last->next = node;
	lst->last = new_lst->last;
	lst->size += new_lst->size;
	return (0);
}

static int	ft_case_head(t_lst *lst, t_node *node, t_lst *new_lst)
{
	t_node	*temp;

	temp = node->next;
	lst->head->next = new_lst->head;
	new_lst->head->prev = lst->head;
	temp->prev = new_lst->last;
	new_lst->last->next = temp;
	lst->size += new_lst->size;
	return (0);
}

static int	ft_case_last(t_lst *lst, t_lst *new_lst)
{
	lst->last->next = new_lst->head;
	new_lst->head->prev = lst->last;
	new_lst->last->next = lst->head;
	lst->head->prev = new_lst->head;
	lst->last = new_lst->last;
	lst->size += new_lst->size;
	return (0);
}

static int	ft_others(t_lst *lst, t_node *node, t_lst *new_lst)
{
	t_node	*temp;

	temp = node->next;
	node->next = new_lst->head;
	new_lst->head->prev = node;
	temp->prev = new_lst->last;
	new_lst->last->next = temp;
	lst->size += new_lst->size;
	return (0);
}
