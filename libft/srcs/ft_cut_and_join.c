/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_and_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 18:26:09 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/16 20:09:42 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_cut_and_join(char *s1, char *s2, int start, int to_free)
{
	char	*s;

	if (!(s = ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	ft_strncpy(s, s1, start);
	ft_strcpy(s + start, s2);
	ft_strcpy(s + start + ft_strlen(s2), s1 + start);
	if (to_free == 1 || to_free == 3)
		free(s1);
	if (to_free == 2 || to_free == 3)
		free(s2);
	return (s);
}
