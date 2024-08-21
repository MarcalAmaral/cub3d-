/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_duplst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:12:43 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/03 14:09:47 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

t_lst	*ft_duplst(t_lst *ori_lst,
			t_node (*ft_cpy(t_node *)), int (*add_n)(t_lst *, t_node *))
{
	t_lst	*new_lst;
	t_node	*node;
	t_node	*new_node;
	int		i;

	if (!ori_lst)
		return (NULL);
	if (ori_lst->size == 0)
		return (NULL);
	new_lst = ft_init_lst();
	if (!new_lst)
		return (NULL);
	i = 1;
	node = ori_lst->head;
	while (i <= ori_lst->size)
	{
		new_node = ft_cpy(node);
		if (!new_node)
			return (NULL);
		add_n(new_lst, new_node);
		node = node->next;
		i++;
	}
	return (new_lst);
}
