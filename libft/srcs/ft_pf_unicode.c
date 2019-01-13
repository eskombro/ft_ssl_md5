/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:35:16 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/16 20:51:06 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*wchar_to_str(wchar_t ch, t_ret *ret)
{
	char	*tmp;

	tmp = ft_strnew(5);
	if (ch < 128)
		tmp[0] = (char)ch;
	else if (ch < 2048)
	{
		tmp[0] = (ch >> 6) + 0xC0;
		tmp[1] = (ch & 0x3F) + 0x80;
	}
	else if (ch < 65536)
	{
		tmp[0] = (ch >> 12) + 0xE0;
		tmp[1] = ((ch >> 6) & 0x3F) + 0x80;
		tmp[2] = (ch & 0x3F) + 0x80;
	}
	else
	{
		tmp[0] = (ch >> 18) + 0xF0;
		tmp[1] = ((ch >> 12) & 0x3F) + 0x80;
		tmp[2] = ((ch >> 6) & 0x3F) + 0x80;
		tmp[3] = (ch & 0x3F) + 0x80;
	}
	tmp[0] == 0 && ch < 128 ? ret->size = 1 : 0;
	return (tmp);
}

void		handle_wildcard(t_obj *obj, char last_char, va_list ap)
{
	if (last_char == '.')
	{
		obj->precision = va_arg(ap, int);
		obj->precision < 0 ? obj->precision = -1 : 0;
	}
	else
	{
		obj->min_width = va_arg(ap, int);
		obj->min_width < 0 ? obj->flags = obj->flags | MOINS : 0;
		obj->min_width < 0 ? obj->min_width *= -1 : 0;
	}
}
