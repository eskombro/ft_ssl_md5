/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maltabtab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:11:58 by sjimenez          #+#    #+#             */
/*   Updated: 2017/11/28 04:26:07 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_create(int size_y, char **tab, char *str)
{
	if (!(tab = (char **)malloc(sizeof(char *) * (size_y + 1))))
		return (NULL);
	tab[0] = ft_strdup(str);
	tab[1] = NULL;
	return (tab);
}

static char	**ft_new(int size_y, char **tab, char *str)
{
	char	**t;
	int		i;

	i = -1;
	if (!(t = (char **)malloc(sizeof(char *) * (size_y + 1))))
		return (NULL);
	t[size_y] = NULL;
	while (tab[++i])
		t[i] = ft_strdup(tab[i]);
	t[i] = ft_strdup(str);
	i = -1;
	while (tab[++i])
		ft_strdel(&tab[i]);
	ft_strdel(&tab[i]);
	free(tab);
	tab = NULL;
	return (t);
}

char		**ft_maltabtab(char **tab, char *str)
{
	int size_y;

	if (!str)
		return (NULL);
	if (!tab)
	{
		if ((tab = ft_create(1, tab, str)) == NULL)
			return (NULL);
	}
	else
	{
		size_y = 0;
		while (tab[size_y])
			size_y++;
		if ((tab = ft_new(size_y + 1, tab, str)) == NULL)
			return (NULL);
	}
	return (tab);
}
