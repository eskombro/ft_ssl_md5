/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:18:34 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/08 19:37:17 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t t;

	i = 0;
	if (s2[i] == '\0')
		return ((char *)s1);
	while (s1[i])
	{
		t = 0;
		while (s1[i + t] == s2[t])
		{
			if (i + t < n && s2[t + 1] == '\0')
				return ((char *)s1 + i);
			t++;
		}
		i++;
	}
	return (NULL);
}
