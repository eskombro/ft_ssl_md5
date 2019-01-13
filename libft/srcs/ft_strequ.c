/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 22:57:52 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/12 07:12:14 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (s1[0] == s2[0] && s1[0] == '\0')
		return (1);
	while (i < ft_strlen(s1) + 1)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
