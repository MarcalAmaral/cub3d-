/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_specific_content.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:42:17 by rbutzke           #+#    #+#             */
/*   Updated: 2024/03/28 08:25:32 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

int	ft_remove_specific_content(t_lst *lst, char c)
{
	t_var	var;

	if (!lst)
		return (-1);
	if (!lst->head && !lst->last)
		return (-1);
	var.i = 0;
	var.current_node = lst->head;
	var.next_node = var.current_node->next;
	while (var.i <= lst->size)
	{
		if (c == var.current_node->c)
			break ;
		var.current_node = var.next_node;
		var.next_node = var.next_node->next;
		var.i++;
	}
	if (c == var.current_node->c)
		return (ft_remove_specific_node(lst, var.current_node));
	return (-1);
}
