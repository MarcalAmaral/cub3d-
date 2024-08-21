/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtrxlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:44:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/04/29 10:48:57 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_mtrxlen(char	**matrix)
{
	int	size;

	if (!matrix)
		return (-1);
	size = 0;
	while (matrix[size])
		size++;
	return (size);
}
