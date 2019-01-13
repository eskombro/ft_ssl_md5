/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 22:35:37 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/12 04:30:48 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;
	t_list	*cpy;
	t_list	*start;

	if (lst == NULL || f == NULL)
		return (NULL);
	start = NULL;
	while (lst)
	{
		cpy = f(lst);
		if (start != NULL)
		{
			if (!(new_list->next = ft_lstnew(cpy->content, cpy->content_size)))
				return (NULL);
			new_list = new_list->next;
		}
		else
		{
			if (!(new_list = ft_lstnew(cpy->content, cpy->content_size)))
				return (NULL);
			start = new_list;
		}
		lst = lst->next;
	}
	return (start);
}
