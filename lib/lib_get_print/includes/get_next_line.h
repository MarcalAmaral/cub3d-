/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:38:05 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/22 12:46:48 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_get_lst
{
	char				c;
	struct s_get_lst	*next;
}	t_get_lst;

void		remode_buffer(char *buffer, int index);
void		cpy_buff_to_lst(char *buffer, t_get_lst **lst, int *is_space);
t_get_lst	*ft_read_files(int fd);
char		*get_next_line(int fd);
void		ft_lst_add_creat(t_get_lst **lst, char content);
char		*cpy_lst_array(t_get_lst *lst);
void		clear(t_get_lst *lst);
int			ft_lstlen(t_get_lst *lst);

#endif