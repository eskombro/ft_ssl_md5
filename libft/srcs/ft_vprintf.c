/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:42:21 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/16 19:42:22 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			v_write_and_close(char *buff, t_int i, t_ret *ret)
{
	write(1, buff, i.buff_cnt);
	free(ret);
	free(buff);
}

int				ft_vprintf(const char *restrict str, va_list ap)
{
	t_int		i;
	char		*buff;
	t_ret		*ret;

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
	v_write_and_close(buff, i, ret);
	return (i.buff_cnt);
}
