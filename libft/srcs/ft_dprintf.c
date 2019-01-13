/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:42:53 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/16 19:43:02 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			dprintf_initialize(char **buff, t_ret **ret, t_int *i, int fd)
{
	if (!(*ret = (t_ret*)ft_memalloc(sizeof(t_ret))))
		exit(-1);
	if (!(*buff = (char*)ft_memalloc(sizeof(char) * REALLOC_SIZE)))
	{
		free(*ret);
		exit(-1);
	}
	i->str_cnt = 0;
	i->buff_cnt = 0;
	i->malloc_cnt = REALLOC_SIZE;
	i->fd = fd;
}

void			dprintf_write_and_close(char *buff, t_int i,
				t_ret *ret, va_list ap)
{
	write(i.fd, buff, i.buff_cnt);
	va_end(ap);
	free(ret);
	free(buff);
}

int				ft_dprintf(int fd, const char *restrict str, ...)
{
	t_int		i;
	va_list		ap;
	char		*buff;
	t_ret		*ret;

	va_start(ap, str);
	dprintf_initialize(&buff, &ret, &i, fd);
	while (str[i.str_cnt])
	{
		if (str[i.str_cnt] == '%')
		{
			ret->value = NULL;
			ret->size = 0;
			i.str_cnt++;
			if (!(ret = found_pourcentage((char*)str, ap, &(i.str_cnt), ret)))
				return (-1);
			if (ret->value)
				if (!fill_buff(&buff, &i, ret))
					return (-1);
		}
		else if (!found_no_pourcentage(&buff, str, &i))
			return (-1);
	}
	dprintf_write_and_close(buff, i, ret, ap);
	return (i.buff_cnt);
}
