/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_tab_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:39:00 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/13 16:38:45 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_sort_tab_int(int *tab, size_t len, size_t ord)
{
	size_t		i;
	int			temp;

	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < len - 1)
	{
		if ((tab[i] > tab[i + 1] && ord == 1) ||
				(tab[i] < tab[i + 1] && ord == 2))
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = -1;
		}
		i++;
	}
	return (tab);
}
