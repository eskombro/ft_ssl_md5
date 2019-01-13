/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:35:49 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/16 19:35:53 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	modify_len(intmax_t value, t_obj obj)
{
	if (ft_tolower(obj.type) == 'd' || obj.type == 'i')
	{
		obj.len_mod == 'H' ? (value = (char)value) : 0;
		obj.len_mod == 'h' ? (value = (short)value) : 0;
		obj.len_mod == 'l' ? (value = (long)value) : 0;
		obj.len_mod == 'L' ? (value = (long long)value) : 0;
		obj.len_mod == 'j' ? (value = (intmax_t)value) : 0;
		obj.len_mod == 'z' ? (value = (long long)value) : 0;
		obj.len_mod == 0 ? (value = (int)value) : 0;
	}
	else if (ft_strchr("oOuUxXb", obj.type))
	{
		obj.len_mod == 'H' ? (value = (unsigned char)value) : 0;
		obj.len_mod == 'h' ? (value = (unsigned short)value) : 0;
		obj.len_mod == 'l' ? (value = (unsigned long)value) : 0;
		obj.len_mod == 'L' ? (value = (unsigned long long)value) : 0;
		obj.len_mod == 'j' ? (value = (uintmax_t)value) : 0;
		obj.len_mod == 'z' ? (value = (size_t)value) : 0;
		obj.len_mod == 0 ? (value = (unsigned int)value) : 0;
	}
	return (value);
}

char		*add_precision(char *value, t_obj obj)
{
	int		tmp;
	char	*filler;

	if (ft_tolower(obj.type) == 's')
	{
		if (!(value = ft_strsub_free(value, 0, obj.precision)))
			return (NULL);
	}
	else if (ft_tolower(obj.type) != 'c')
	{
		tmp = obj.precision - (int)ft_strlen(value);
		value[0] == '-' ? tmp++ : 0;
		if (tmp > 0)
		{
			if (!(filler = (char*)ft_memalloc(sizeof(char) * (tmp + 1))))
				return (NULL);
			ft_memset(filler, '0', tmp);
			if (!(value = ft_strjoin_free(filler, value, 3)))
				return (NULL);
		}
	}
	return (value);
}

char		*add_espace_plus_diez(t_obj obj, char *value)
{
	if (obj.type == 'p' || (obj.flags & DIEZ &&
		ft_tolower(obj.type) == 'x' && ft_atoi(value) && obj.precision != 0))
		if (!(value = ft_strjoin_free("0x", value, 2)))
			return (NULL);
	obj.type == 'X' && obj.flags & DIEZ
		&& value[1] == 'x' ? value[1] = ft_toupper(value[1]) : 0;
	if ((ft_tolower(obj.type) == 'd' || obj.type == 'i') && value[0] != '-')
	{
		if (obj.flags & PLUS)
		{
			if (!(value = ft_strjoin_free("+", value, 2)))
				return (NULL);
		}
		else if (obj.flags & ESPACE)
			if (!(value = ft_strjoin_free(" ", value, 2)))
				return (NULL);
	}
	if (ft_tolower(obj.type) == 'o' && (obj.flags & DIEZ) && value[0] != '0'
		&& obj.precision != 0 && obj.precision <=
		(int)ft_strlen(ft_itoa(ft_atoi(value))))
		if (!(value = ft_strjoin_free("0", value, 2)))
			return (NULL);
	return (value);
}

char		*add_min_width(t_ret *ret, int tmp, t_obj obj)
{
	char	*fil;

	if (!(fil = (char*)ft_memalloc(sizeof(char) * (tmp + 1))))
		return (NULL);
	ft_memset(fil, ' ', tmp);
	((obj.flags & ZERO) && !(obj.flags & MOINS) && ((obj.precision == -1 &&
		!ft_strchr("sScC", obj.type)) || ft_strchr("sScC", obj.type))) ?
		ft_memset(fil, '0', tmp) : 0;
	if (obj.flags & MOINS)
	{
		ret->value = ft_strrealloc_pf(ret->value,
			tmp + ft_strlen(ret->value) + ret->size, ret);
		ft_memcpy(ret->value + ft_strlen(ret->value) + ret->size, fil, tmp);
		ret->size += ft_strlen(ret->value + 1) + !ret->size;
		free(fil);
		return (ret->value);
	}
	fil = ft_strrealloc_pf(fil, tmp + ft_strlen(ret->value) + ret->size, ret);
	ft_memcpy(fil + tmp, ret->value, ft_strlen(ret->value) + ret->size);
	free(ret->value);
	ret->value = fil;
	ret->size += ft_strlen(ret->value);
	return (ret->value);
}

char		*ft_strrealloc_pf(char *s, int size, t_ret *ret)
{
	char	*tmp;

	tmp = (char*)ft_memalloc(sizeof(char) * (size + 1));
	ft_memcpy(tmp, s, ft_strlen(s) + ret->size);
	free(s);
	return (tmp);
}
