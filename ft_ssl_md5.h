/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:06 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/15 01:37:41 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include "libft.h"

typedef struct		s_ssl
{
	uint32_t		*md_buff;
	uint32_t		*abcd;
	char			*final_str;
	uint32_t		g;
	uint32_t		f;
}					t_ssl;

/*
** print_debbug.c
*/

void				print_bits(unsigned char c);
void				print_buff_bits(char *buff, uint64_t expect_ct);
void				print_debbug(char *buff, uint64_t expect_ct);

#endif
