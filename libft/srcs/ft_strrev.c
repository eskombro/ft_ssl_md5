/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:29:33 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/09 23:22:09 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	size_t	d;
	size_t	f;
	char	temp;

	if (s == NULL)
		return (NULL);
	d = 0;
	f = ft_strlen(s) - 1;
	while (f > d)
	{
		temp = s[d];
		s[d++] = s[f];
		s[f--] = temp;
	}
	return (s);
}
