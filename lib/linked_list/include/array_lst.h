/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_lst.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42so.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:47:19 by rbutzke           #+#    #+#             */
/*   Updated: 2024/08/01 12:59:01 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_LST_H
# define ARRAY_LST_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	char			c;
	struct s_node	*next;
	struct s_node	*prev;
}			t_node;

typedef struct s_lst
{
	t_node		*head;
	t_node		*last;
	int			size;
}			t_lst;

typedef struct s_var_array_list
{
	t_node	*current_node;
	t_node	*next_node;
	t_node	*prev_node;
	t_node	*temp_node;
	t_node	*head;
	t_node	*last;
	t_node	*second;
	t_node	*second_last;
	int		i;
}			t_var;

t_lst	*ft_init_lst(void);
t_lst	*ft_duplst(t_lst *ori_lst,
			t_node (*ft_cpy(t_node *)), int (*add_n)(t_lst *, t_node *));
t_lst	*ft_create_lst_add_str(char *array);
t_node	*ft_init_node(char c);
t_node	*ft_cpynode(t_node *node_origin);
t_node	*ft_remove_return_node(t_lst *lst, t_node *node);
int		ft_create_node_add_back(t_lst *lst, char content);
int		ft_add_node_back(t_lst *lst, t_node *node);
int		ft_create_add_node_front(t_lst *lst, char content);
int		ft_add_node_front(t_lst *lst, t_node *node);;
int		ft_remove_node_front(t_lst *lst);
int		lst_rmv_back(t_lst *lst);
int		ft_remove_specific_node(t_lst *lst, t_node *node);
int		ft_remove_specific_content(t_lst *lst, char c);
int		ft_delete_list(t_lst *lst);
int		ft_add_string_in_list(t_lst *lst, char *array);
int		ft_lst_btwn_lst(t_lst *lst_d, t_node *n_a, t_node *n_b, t_lst *lst_n);
int		ft_find_str_inlist(t_lst *lst, char *str, int size);
char	*ft_cpy_lst_to_array(t_lst *lst);
void	ft_putlst_fd(t_lst *lst, int new_line, int fd);
int		insert_node_between(t_lst *lst, t_node *node, t_lst *new_lst);
t_node	*find_type_rtrn_ptr(t_lst *lst, int type);
int		ft_find_head(t_lst *lst, char *str, int size);
int		ft_find_last(t_lst *lst, char *str, int size);

#endif
