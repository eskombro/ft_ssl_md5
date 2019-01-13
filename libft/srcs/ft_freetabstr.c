/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetabstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 05:19:29 by sjimenez          #+#    #+#             */
/*   Updated: 2018/02/09 15:30:35 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_freetabstr(char **tab)
{
	int		i;

	if (tab == NULL)
		return ;
	i = -1;
	while (tab[++i])
		ft_strdel(&tab[i]);
	ft_strdel(&tab[i]);
	free(tab);
}
