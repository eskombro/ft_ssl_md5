/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:40:16 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/16 19:41:38 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char		*ft_strsub_free(char *s, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (!(tmp = (char*)malloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		tmp[i] = s[i + start];
		i++;
	}
	tmp[i] = '\0';
	free(s);
	return (tmp);
}
