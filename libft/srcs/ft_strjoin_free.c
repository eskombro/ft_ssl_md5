/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 10:14:32 by sjimenez          #+#    #+#             */
/*   Updated: 2018/04/10 06:22:20 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ** Cree nouvelle chaine malloc s1 + s2 et free les chaines passees en param
*/

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, size_t to_free)
{
	char	*str;
	size_t	s1_size;
	size_t	s2_size;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	if (!(str = (char*)malloc(sizeof(char) * (s1_size + s2_size + 1))))
		return (NULL);
	str[s1_size + s2_size] = 0;
	ft_strncpy(str, s1, s1_size);
	ft_strncpy(str + s1_size, s2, s2_size);
	if (to_free == 1)
		ft_strdel(&s1);
	else if (to_free == 2)
		ft_strdel(&s2);
	else if (to_free == 3)
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
	return (str);
}
