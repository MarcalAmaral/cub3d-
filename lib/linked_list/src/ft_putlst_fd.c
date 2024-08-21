/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:35:47 by rbutzke           #+#    #+#             */
/*   Updated: 2024/06/03 14:20:03 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_lst.h"

void	ft_putlst_fd(t_lst *lst, int new_line, int fd)
{
	int		i;
	t_node	*current;

	if (fd < 0)
		return ;
	if (!lst)
		return ;
	if (lst->size == 0)
		return ;
	i = 1;
	current = lst->head;
	while (i <= lst->size)
	{
		write(fd, &current->c, 1);
		current = current->next;
		i++;
	}
	if (new_line)
		write(fd, "\n", 1);
}
