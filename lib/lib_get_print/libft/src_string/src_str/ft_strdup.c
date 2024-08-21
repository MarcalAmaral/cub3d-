/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:23:56 by rbutzke           #+#    #+#             */
/*   Updated: 2024/02/11 17:11:59 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*new_array;
	unsigned int	size;

	if (!s)
	{
		new_array = ft_calloc(sizeof(char), 1);
		return (new_array);
	}
	size = ft_strlen(s) + 1;
	new_array = malloc(size * sizeof(char));
	if (new_array == NULL)
		return (NULL);
	ft_strlcpy(new_array, s, size);
	return (new_array);
}
