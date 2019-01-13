/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 01:49:20 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/12 02:37:22 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*item;

	if (!(item = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		item->content_size = 0;
		item->content = NULL;
	}
	else
	{
		if (!(item->content = malloc(content_size)))
			return (NULL);
		ft_memcpy(item->content, content, content_size);
		item->content_size = content_size;
	}
	item->next = NULL;
	return (item);
}
