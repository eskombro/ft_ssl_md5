/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:46:01 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/12 06:09:33 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*s1c;
	char	*s2c;

	s1c = (char*)s1;
	s2c = (char*)s2;
	while (n--)
	{
		if ((unsigned char)*s1c != (unsigned char)*s2c)
			return ((unsigned char)*s1c - (unsigned char)*s2c);
		s1c++;
		s2c++;
	}
	return (0);
}
