/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 04:35:13 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/28 04:41:25 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim_free(char *s)
{
	char		*s2;

	if (s == NULL)
		return (NULL);
	s2 = ft_strtrim(s);
	ft_strdel(&s);
	return (s2);
}
