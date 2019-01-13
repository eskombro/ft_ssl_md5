/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:37:53 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/16 19:37:56 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		itoa_len(long long nbr, int base)
{
	int		len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr > 0)
		nbr = -nbr;
	else if (base == 10)
		len++;
	while (nbr < 0)
	{
		len++;
		nbr /= base;
	}
	return (len);
}

char			*ft_lltoa_base(long long nbr, int base, int upper)
{
	int		len;
	char	*s;
	char	base_set[17];

	upper ? ft_strcpy(base_set, "0123456789ABCDEF") :
	ft_strcpy(base_set, "0123456789abcdef");
	len = itoa_len(nbr, base);
	if (!(s = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (nbr >= 0)
		nbr = -nbr;
	else if (base == 10)
		s[0] = '-';
	s[len--] = '\0';
	if (nbr == 0)
		s[0] = '0';
	while (nbr < 0)
	{
		s[len--] = base_set[-(nbr % base)];
		nbr /= base;
	}
	return (s);
}
