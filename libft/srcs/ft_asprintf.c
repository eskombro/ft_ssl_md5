/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:43:11 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/16 19:43:14 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*assign_and_close(char *buff, t_ret *ret, va_list ap)
{
	va_end(ap);
	free(ret);
	return (buff);
}

int				ft_asprintf(char **line, const char *str, ...)
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
	*line = assign_and_close(buff, ret, ap);
	return (i.buff_cnt);
}
