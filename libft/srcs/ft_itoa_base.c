/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 04:20:55 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/30 04:38:47 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itoa_n_len(int n, int base)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n <= -base || n >= base)
	{
		n /= base;
		len++;
	}
	len++;
	return (len);
}

char			*ft_itoa_base(int n, int base)
{
	char	*s;
	size_t	i;
	int		nb;
	size_t	len;
	char	*char_base;

	i = 0;
	nb = n;
	char_base = "0123456789ABCDEF";
	len = ft_itoa_n_len(n, base);
	if (!(s = ft_memalloc(len + 1)))
		return (NULL);
	if (nb > 0)
		nb = -nb;
	while (nb <= -base)
	{
		s[i++] = char_base[-(nb % base)];
		nb /= base;
	}
	s[i++] = char_base[-nb];
	if (n < 0)
		s[i] = '-';
	return (ft_strrev(s));
}
