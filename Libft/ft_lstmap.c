/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <mregada-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:34:15 by mregada-          #+#    #+#             */
/*   Updated: 2025/02/08 12:28:09 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	del_new_list(void *list, void (*del)(void *))
{
	t_list	*new_list;
	t_list	*temp;

	new_list = (t_list *)list;
	while (new_list)
	{
		temp = new_list->next;
		(*del)(new_list->content);
		free (new_list);
		new_list = temp;
	}
}

static void	ft_asign(t_list **new_list, t_list *newnode, t_list	**new_index)
{
	if (!*new_list)
		*new_list = newnode;
	else
		(*new_index)->next = newnode;
	*new_index = newnode;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void*))
{
	t_list	*new_list;
	t_list	*new_index;
	t_list	*index;
	t_list	*newnode;

	new_list = NULL;
	index = lst;
	while (index)
	{
		newnode = (t_list *)malloc(sizeof (t_list));
		if (!newnode)
		{
			del_new_list(new_list, del);
			return (NULL);
		}
		newnode->content = (*f)(index->content);
		newnode->next = NULL;
		ft_asign(&new_list, newnode, &new_index);
		index = index->next;
	}
	return (new_list);
}
