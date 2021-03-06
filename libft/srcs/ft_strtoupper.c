/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 05:10:04 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/30 05:10:24 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtoupper(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		s[i] = ft_toupper(s[i]);
	return (s);
}
