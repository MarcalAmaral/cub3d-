/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtrxdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:01:22 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/14 12:51:10 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_mtrxdup(char **origin_matrix)
{
	char	**dest_matrix;
	int		size;
	int		i;

	dest_matrix = NULL;
	if (!origin_matrix)
		return (dest_matrix);
	size = 0;
	while (origin_matrix[size])
		size++;
	dest_matrix = ft_calloc(sizeof (char *), size +1);
	i = 0;
	while (origin_matrix[i])
	{
		dest_matrix[i] = ft_strdup(origin_matrix[i]);
		i++;
	}
	return (dest_matrix);
}
