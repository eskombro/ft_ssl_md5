/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstrnumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 23:12:18 by sjimenez          #+#    #+#             */
/*   Updated: 2018/02/12 16:51:34 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Accepte nombres entiers negatifs et positifs ('-' en premier caracter)
*/

int		ft_isstrnumber(char *s)
{
	int		i;

	i = -1;
	if (!s || !*s)
		return (0);
	if (s[0] == '-')
		i++;
	while (s[++i])
		if (s[i] > '9' || s[i] < '0')
			return (0);
	return (1);
}
