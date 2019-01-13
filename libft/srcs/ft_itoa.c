/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:12:18 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/30 04:21:13 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itoa_n_len(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n <= -10 || n >= 10)
	{
		n /= 10;
		len++;
	}
	len++;
	return (len);
}

char			*ft_itoa(int n)
{
	char	*s;
	size_t	i;
	int		nb;
	size_t	len;

	i = 0;
	nb = n;
	len = ft_itoa_n_len(n);
	if (!(s = ft_memalloc(len + 1)))
		return (NULL);
	if (nb > 0)
		nb = -nb;
	while (nb <= -10)
	{
		s[i++] = -(nb % 10) + 48;
		nb /= 10;
	}
	s[i++] = -nb + 48;
	if (n < 0)
		s[i] = '-';
	return (ft_strrev(s));
}
