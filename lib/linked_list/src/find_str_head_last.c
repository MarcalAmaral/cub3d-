/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_str_head_last.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:01:17 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/03 14:11:02 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

int	ft_find_last(t_lst *lst, char *str, int size)
{
	t_node	*node;
	int		index;

	index = size -1;
	node = lst->last;
	while (index >= 0)
	{
		if (node->c != str[index])
			break ;
		node = node->prev;
		index--;
	}
	if (index +1 == 0)
		return (1);
	return (0);
}

int	ft_find_head(t_lst *lst, char *str, int size)
{
	t_node	*node;
	int		index;

	index = 0;
	node = lst->head;
	while (index <= size && str[index])
	{
		if (node->c != str[index])
			break ;
		node = node->next;
		index++;
	}
	if (index == size)
		return (1);
	return (0);
}
