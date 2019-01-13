/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 01:02:31 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/09 22:13:49 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	size;
	char	*str;

	if (s == NULL)
		return (NULL);
	while (s[0] == ' ' || s[0] == '\n' || s[0] == '\t')
		s++;
	size = ft_strlen(s);
	while (size > 0 && (s[size - 1] == ' '
				|| s[size - 1] == '\n' || s[size - 1] == '\t'))
		size--;
	if (!(str = ft_strnew(size)))
		return (NULL);
	ft_memmove(str, s, size);
	str[size] = '\0';
	return (str);
}
