/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 20:04:33 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/16 20:04:35 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*conv_char_string(t_obj obj, t_ret *ret, va_list ap)
{
	if (ft_isupper(obj.type) || obj.len_mod == 'l')
		return (conv_char_string_unicode(obj, ret, ap));
	if (ft_tolower(obj.type) == 's')
	{
		if (!(ret->value = (va_arg(ap, char*))))
		{
			if (!(ret->value = ft_strdup("(null)")))
				return (NULL);
		}
		else if (!(ret->value = ft_strdup(ret->value)))
			return (NULL);
	}
	else if (ft_tolower(obj.type) == 'c')
	{
		ret->value = (char*)ft_memalloc(sizeof(char) * 2);
		if (obj.flags & NXT_CHAR)
			ret->value[0] = obj.nxt_char;
		else
		{
			ret->value[0] = (unsigned char)va_arg(ap, int);
			ret->value[0] == 0 ? ret->size = 1 : 0;
		}
	}
	return (ret->value);
}

char			*conv_char_string_unicode(t_obj obj, t_ret *ret, va_list ap)
{
	wchar_t		*w;

	if (ft_tolower(obj.type) == 's')
	{
		if (!(w = (va_arg(ap, wchar_t*))))
		{
			if (!(ret->value = ft_strdup("(null)")))
				return (NULL);
		}
		else
		{
			if (!(ret->value = ft_strdup("")))
				return (NULL);
			while (*w && (obj.precision == -1 || (int)ft_strlen(ret->value) +
			(int)ft_strlen(wchar_to_str(*w, ret)) <= obj.precision))
				ret->value = ft_strjoin_free(ret->value,
					wchar_to_str(*w++, ret), 3);
		}
		return (ret->value);
	}
	if (obj.flags & NXT_CHAR)
		ret->value[0] = obj.nxt_char;
	else
		ret->value = wchar_to_str(va_arg(ap, wchar_t), ret);
	return (ret->value);
}

char			*conv_numbers(t_obj obj, t_ret *ret, va_list ap)
{
	intmax_t	tmp;
	int			base;

	base = 10;
	ft_tolower(obj.type) == 'o' ? (base = 8) : 0;
	ft_tolower(obj.type) == 'b' ? (base = 2) : 0;
	ft_tolower(obj.type) == 'x' || ft_tolower(obj.type) == 'p' ? base = 16 : 0;
	tmp = modify_len(va_arg(ap, uintmax_t), obj);
	if (!tmp && obj.precision == 0)
	{
		if (!(ret->value = ft_strdup("")))
			return (NULL);
	}
	else
	{
		if (ft_tolower(obj.type) == 'd' || obj.type == 'i')
		{
			if (!(ret->value = ft_lltoa_base(tmp, base, ft_isupper(obj.type))))
				return (NULL);
		}
		else if (!(ret->value =
			ft_ulltoa_base(tmp, base, ft_isupper(obj.type))))
			return (NULL);
	}
	return (ret->value);
}

t_ret			*conversion(t_obj obj, va_list ap, t_ret *ret)
{
	int			tmp;

	if (ft_strchr("sScC", obj.type))
	{
		if (!(conv_char_string(obj, ret, ap)))
			return (NULL);
	}
	else if (!(conv_numbers(obj, ret, ap)))
		return (NULL);
	if (ft_tolower(obj.type) == 'o' && (obj.flags & DIEZ)
		&& obj.precision <= (int)ft_strlen(ret->value))
		obj.precision != -1 ? obj.precision += 1 : 0;
	obj.precision != -1 ? ret->value = add_precision(ret->value, obj) : 0;
	if (!ret->value || !(ret->value = add_espace_plus_diez(obj, ret->value)))
		return (NULL);
	if ((tmp = obj.min_width - (int)ft_strlen(ret->value) - ret->size) > 0)
		if (!(add_min_width(ret, tmp, obj)))
			return (NULL);
	tmp <= 0 ? ret->size += ft_strlen(ret->value) : 0;
	move_signs(ret, obj);
	return (ret);
}

void			move_signs(t_ret *ret, t_obj obj)
{
	char		*tmp;
	int			i;
	char		c;

	tmp = NULL;
	if (ft_tolower(obj.type) != 'c' && ft_tolower(obj.type) != 's')
	{
		tmp = ft_strchr(ret->value, '-');
		!tmp ? tmp = ft_strchr(ret->value, '+') : 0;
		!tmp ? tmp = ft_strchr(ret->value, 'x') : 0;
		if (!tmp && obj.flags & ESPACE && ft_strchr("dDi", obj.type))
			tmp = ft_strchr(ret->value, ' ');
		if (tmp)
		{
			i = 0;
			while (*(tmp - i - 1) == '0' && tmp - i - 1 >= ret->value)
				i++;
			*tmp == 'x' ? i-- : 0;
			c = *(tmp - i);
			*(tmp - i) = *tmp;
			*tmp = c;
		}
	}
}
