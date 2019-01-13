/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:39:11 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/16 19:57:10 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		itoa_len(unsigned long long nbr, int base)
{
	int		len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		len++;
		nbr /= base;
	}
	return (len);
}

char			*ft_ulltoa_base(unsigned long long nbr, int base, int upper)
{
	int		len;
	char	*s;
	char	base_set[17];

	upper ? ft_strcpy(base_set, "0123456789ABCDEF") :
	ft_strcpy(base_set, "0123456789abcdef");
	len = itoa_len(nbr, base);
	if (!(s = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s[len--] = '\0';
	if (nbr == 0)
		s[0] = '0';
	while (nbr > 0)
	{
		s[len--] = base_set[(nbr % base)];
		nbr /= base;
	}
	return (s);
}
