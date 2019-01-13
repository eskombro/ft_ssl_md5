/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:17:33 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/12 06:55:59 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *s1, const char *s2, size_t size)
{
	size_t s1_size;
	size_t s2_size;
	size_t n;
	size_t i;

	s2_size = ft_strlen(s2);
	s1_size = ft_strlen(s1);
	if (s1_size > size)
		s1_size = size;
	n = s1_size + s2_size;
	if (size > s1_size)
	{
		i = 0;
		while (s1_size + i < size - 1)
		{
			s1[s1_size + i] = s2[i];
			i++;
		}
		s1[s1_size + i] = '\0';
	}
	return (n);
}
