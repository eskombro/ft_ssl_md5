/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:42:35 by sjimenez          #+#    #+#             */
/*   Updated: 2018/01/25 22:31:25 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <inttypes.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# define CONV "sSpdDioOuUxXcCb*#0-+ 123456789.hljz"
# define MOD_PRIO "HhlLjz"
# define OPT_LEN 20
# define REALLOC_SIZE 15

typedef struct	s_int
{
	int			str_cnt;
	int			buff_cnt;
	int			malloc_cnt;
	int			fd;
}				t_int;

typedef struct	s_ret
{
	char		*value;
	int			size;
}				t_ret;

typedef struct	s_flags
{
	char		flag;
	char		pos;
}				t_flags;

enum {NXT_CHAR = 32, ESPACE = 16, PLUS = 8, MOINS = 4, ZERO = 2, DIEZ = 1};

typedef struct	s_obj
{
	char		type;
	int			min_width;
	int			precision;
	char		flags;
	char		len_mod;
	char		nxt_char;

}				t_obj;

char			*add_min_width(t_ret *ret, int tmp, t_obj obj);
char			*add_espace_plus_diez(t_obj obj, char *value);
char			*add_precision(char *value, t_obj obj);
intmax_t		modify_len(intmax_t value, t_obj obj);
int				ft_printf(const char *restrict str, ...);
t_ret			*found_pourcentage(char *str, va_list ap,
				int *curs, t_ret *ret);
char			*ft_strrealloc_pf(char *s, int size, t_ret *ret);
t_ret			*conversion(t_obj obj, va_list ap, t_ret *ret);
void			move_signs(t_ret *ret, t_obj obj);
char			*conv_char_string(t_obj obj, t_ret *ret, va_list ap);
char			*conv_char_string_unicode(t_obj obj, t_ret *ret, va_list ap);
char			*conv_numbers(t_obj obj, t_ret *ret, va_list ap);
char			*wchar_to_str(wchar_t ch, t_ret *ret);
void			initialize(char **buff, t_ret **ret, t_int *i);
int				fill_buff(char **buff, t_int *i, t_ret *ret);
int				found_no_pourcentage(char **buff, const char *str, t_int *i);
int				ft_dprintf(int fd, const char *restrict str, ...);
int				ft_asprintf(char **line, const char *str, ...);
int				ft_vprintf(const char *restrict str, va_list ap);
void			handle_wildcard(t_obj *obj, char last_char, va_list ap);

#endif
