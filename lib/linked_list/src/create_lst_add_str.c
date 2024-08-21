/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst_add_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:10:30 by rbutzke           #+#    #+#             */
/*   Updated: 2024/05/03 09:43:25 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

t_lst	*ft_create_lst_add_str(char *array)
{
	int		i;
	t_lst	*new_lst;

	if (!array)
		return (NULL);
	i = 0;
	new_lst = ft_init_lst();
	while (array[i])
	{
		if (ft_create_node_add_back(new_lst, array[i]))
		{
			write(STDERR_FILENO, "error creation array_list\n", 27);
			return (NULL);
		}
		i++;
	}
	return (new_lst);
}
