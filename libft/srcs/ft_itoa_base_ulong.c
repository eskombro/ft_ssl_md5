/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_ulong.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 20:01:13 by sjimenez          #+#    #+#             */
/*   Updated: 2017/12/07 20:11:24 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itoa_n_len(unsigned long n, unsigned int base)
{
	size_t				len;

	len = 0;
	if (n == 0)
		return (1);
	while (n >= base)
	{
		n /= base;
		len++;
	}
	len++;
	return (len);
}

char			*ft_itoa_base_ulong(unsigned long n, unsigned int base)
{
	char				*s;
	size_t				i;
	unsigned long		nb;
	size_t				len;
	char				*char_base;

	i = 0;
	nb = n;
	char_base = "0123456789ABCDEF";
	len = ft_itoa_n_len(n, base);
	if (!(s = ft_memalloc(len + 1)))
		return (NULL);
	while (nb >= base)
	{
		s[i++] = char_base[nb % base];
		nb /= base;
	}
	s[i++] = char_base[nb];
	return (ft_strrev(s));
}
