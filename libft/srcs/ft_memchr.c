/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:09:08 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/12 06:03:33 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*s1;

	s1 = (char*)s;
	while (n--)
		if ((unsigned char)*s1++ == (unsigned char)c)
			return (s1 - 1);
	return (NULL);
}
