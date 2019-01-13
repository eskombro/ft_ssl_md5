/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:40:34 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/16 20:27:26 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			initialize(char **buff, t_ret **ret, t_int *i)
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
}

int				found_no_pourcentage(char **buff, const char *str, t_int *i)
{
	if (i->buff_cnt == i->malloc_cnt - 1)
	{
		if (!(*buff = ft_strrealloc(*buff, i->buff_cnt + REALLOC_SIZE)))
			return (0);
		i->malloc_cnt = i->buff_cnt + REALLOC_SIZE;
	}
	(*buff)[(i->buff_cnt)++] = str[(i->str_cnt)++];
	return (1);
}

int				fill_buff(char **buff, t_int *i, t_ret *ret)
{
	if (!(*buff = ft_strrealloc(*buff, i->buff_cnt + ret->size + REALLOC_SIZE)))
		return (0);
	i->malloc_cnt = i->buff_cnt + ret->size + REALLOC_SIZE;
	ft_memcpy(*buff + i->buff_cnt, ret->value, ret->size);
	free(ret->value);
	i->buff_cnt += ret->size;
	return (1);
}

void			write_and_close(char *buff, t_int i, t_ret *ret, va_list ap)
{
	write(1, buff, i.buff_cnt);
	va_end(ap);
	free(ret);
	free(buff);
}

int				ft_printf(const char *restrict str, ...)
{
	t_int		i;
	va_list		ap;
	char		*buff;
	t_ret		*ret;

	va_start(ap, str);
	initialize(&buff, &ret, &i);
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
	write_and_close(buff, i, ret, ap);
	return (i.buff_cnt);
}
