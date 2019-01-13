/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 12:47:54 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/16 19:30:07 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			read_line(int fd, char *str, char *bf)
{
	int			c;

	if (!(str = (char*)ft_memalloc(BUFF_SIZE + 1)))
		return (-1);
	if ((c = read(fd, str, BUFF_SIZE)) < 0)
		return (c);
	ft_strcat(bf, str);
	free(str);
	return (c);
}

static int			send_line(char *bf, int c, char **line)
{
	char		*temp;

	if (!(*line = ft_memalloc(ft_strlen(bf) + 1)))
		return (-1);
	ft_memmove(*line, bf, ft_strlen(bf));
	if ((temp = ft_memchr(*line, '\n', ft_strlen(*line))))
	{
		*temp = '\0';
		ft_strcpy(bf, temp + 1);
	}
	else
	{
		if (c == 0 && bf[0] == 0)
		{
			ft_strdel(&bf);
			return (0);
		}
		ft_bzero(bf, ft_strlen(bf));
	}
	return (1);
}

int					ft_gnl(int fd, char **line)
{
	static char	*bf[200 + 1];
	char		*str;
	int			c;

	c = 1;
	str = NULL;
	if (fd < 0 || !line || fd > 200 || BUFF_SIZE <= 0)
		return ((!line || (*line = NULL) == NULL ? -1 : -1));
	while (c)
	{
		if (bf[fd] == NULL)
		{
			if (!(bf[fd] = ft_memalloc(BUFF_SIZE + 1)))
				return (-1);
		}
		else if (!(ft_str_realloc(&bf[fd], ft_strlen(bf[fd]) + BUFF_SIZE + 1)))
			return (-1);
		if ((!ft_memchr(bf[fd], '\n', ft_strlen(bf[fd]))))
			if ((c = read_line(fd, str, bf[fd])) == -1)
				return (-1);
		if (ft_memchr(bf[fd], '\n', ft_strlen(bf[fd])) || c != BUFF_SIZE)
			return (send_line(bf[fd], c, line));
	}
	return (0);
}
