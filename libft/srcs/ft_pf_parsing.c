/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:35:31 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/16 20:49:09 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_obj			create_obj(void)
{
	t_obj		obj;

	obj.precision = -1;
	obj.flags = 0;
	obj.type = '\0';
	obj.len_mod = '\0';
	obj.min_width = 0;
	return (obj);
}

void			found_len_mod(char *str, int *curs, t_obj *obj, int len)
{
	char		mod_tmp;

	if (str[*curs + 1] == str[*curs] && len > 2)
		mod_tmp = ft_toupper(str[(*curs)++]);
	else
		mod_tmp = str[*curs];
	if (!obj->len_mod || (ft_strlen(ft_strchr(MOD_PRIO, mod_tmp))
				< ft_strlen(ft_strchr(MOD_PRIO, obj->len_mod))))
		obj->len_mod = mod_tmp;
}

void			found_precision(char *str, int *curs, t_obj *obj)
{
	if (ft_isdigit(str[*curs + 1]) && str[*curs] != '0')
	{
		obj->precision = ft_atoi(&str[++(*curs)]);
		while (ft_isdigit(str[*curs + 1]))
			*curs += 1;
	}
	else
		obj->precision = 0;
}

void			parsing(char *str, int *curs, t_obj *obj, int len)
{
	char		flg[6];

	ft_strcpy(flg, " +-0#");
	if (len > OPT_LEN)
	{
		obj->type = str[*curs];
		ft_isupper(obj->type) && obj->type != 'X' ? obj->len_mod = 'l' : 0;
	}
	else if (ft_isalpha(str[*curs]))
		found_len_mod(str, curs, obj, len);
	else if (str[*curs] == '.')
		found_precision(str, curs, obj);
	else if (str[*curs] > '0' && str[*curs] <= '9')
	{
		obj->min_width = ft_atoi(&str[*curs]);
		while (ft_isdigit(str[*curs + 1]))
			*curs += 1;
	}
	else
		obj->flags = obj->flags |
		ft_iterative_power(2, ft_strlen(ft_strchr(flg, str[*curs])) - 1);
}

t_ret			*found_pourcentage(char *str, va_list ap, int *curs, t_ret *ret)
{
	int			len;
	t_obj		obj;
	char		*ptr;

	obj = create_obj();
	while (!obj.type && str[*curs] && (ptr = ft_strchr(CONV, str[*curs])))
	{
		len = ft_strlen(ptr);
		if (str[*curs] == '*')
			handle_wildcard(&obj, str[*curs - 1], ap);
		else
			parsing(str, curs, &obj, len);
		*curs += 1;
	}
	if (!obj.type)
	{
		obj.type = 'c';
		obj.flags = obj.flags | NXT_CHAR;
		if (!(obj.nxt_char = str[(*curs)]))
			return (ret);
		else
			*curs += 1;
	}
	return (conversion(obj, ap, ret));
}
