/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:38:03 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/22 12:46:46 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lst_add_creat(t_get_lst **lst, char content)
{
	t_get_lst	*new_node;
	t_get_lst	*temp;

	new_node = malloc (sizeof(t_get_lst));
	if (!lst || !new_node)
		return ;
	new_node->c = content;
	new_node->next = NULL;
	if (!(*lst))
	{
		*lst = new_node;
		return ;
	}
	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}

char	*cpy_lst_array(t_get_lst *lst)
{
	char		*next_line;
	t_get_lst	*temp;
	int			size;
	int			i;

	size = ft_lstlen(lst);
	next_line = malloc (sizeof(char) *(size +1));
	if (!next_line)
	{
		clear(lst);
		return (NULL);
	}
	i = 0;
	while (lst)
	{
		next_line[i] = lst->c;
		i++;
		temp = lst;
		lst = lst->next;
		free(temp);
	}
	next_line[size] = '\0';
	return (next_line);
}

void	clear(t_get_lst *lst)
{
	t_get_lst	*temp;

	while (lst)
	{
		temp = lst;
		lst = lst->next;
		free(temp);
	}
}

int	ft_lstlen(t_get_lst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
