/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 12:44:36 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/10 19:28:33 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strrealloc(char *s, size_t size)
{
	char	*tmp;

	if (!(tmp = (char*)ft_memalloc(size)))
		return (NULL);
	ft_strcpy(tmp, s);
	ft_memdel((void**)&s);
	return (tmp);
}
