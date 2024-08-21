/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_lst_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:19:32 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/12 19:18:22 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

char	*ft_cpy_lst_to_array(t_lst *lst)
{
	t_var	var;
	char	*str;
	int		i;

	if (!lst || lst->size == 0)
		return (NULL);
	str = malloc(sizeof(char) * (lst->size +2));
	if (!str)
		return (NULL);
	var.current_node = lst->head;
	var.i = 1;
	i = 0;
	while (var.i <= lst->size)
	{
		str[i] = var.current_node->c;
		var.current_node = var.current_node->next;
		var.i++;
		i++;
	}
	str[i] = '\0';
	str[i++] = '\0';
	return (str);
}
