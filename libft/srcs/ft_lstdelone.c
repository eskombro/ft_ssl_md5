/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 03:22:45 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/13 16:32:21 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	t_list *lst;

	if (alst == NULL || del == NULL)
		return ;
	lst = *alst;
	del(lst->content, lst->content_size);
	free(lst);
	*alst = NULL;
}
