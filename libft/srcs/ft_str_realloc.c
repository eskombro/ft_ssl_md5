/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 12:44:36 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/16 19:13:22 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_realloc(char **s, size_t size)
{
	char	*temp;

	if (!(temp = (char*)ft_memalloc(size)))
		return (0);
	ft_strcpy(temp, *s);
	free(*s);
	*s = temp;
	return (1);
}
