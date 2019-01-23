/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:06 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/23 00:35:05 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include "libft.h"

typedef struct	s_ssl
{
	char		algo;
	uint32_t	*md_buff;
	uint32_t	*v;
	uint32_t	*final_str;
	uint32_t	*final_str_uint;
	uint32_t	g;
	uint32_t	f;
	int			chunk_tt;
	int			chunk_current;
}				t_ssl;

/*
** main.c
*/

uint32_t		*initialize_md_buff(int buff_size, char algo);
uint32_t		rot_32_left(uint32_t base, uint32_t rounds);
uint32_t		rot_32_right(uint32_t base, uint32_t rounds);

/*
** print_debbug.c
*/

void			print_bits(unsigned char c);
void			print_buff_bits(char *buff, uint64_t expect_ct);
void			print_debbug(char *buff, uint64_t expect_ct);

/*
** md5.c
*/

uint32_t		md5_aux(uint32_t b, uint32_t c, uint32_t d, char funct);
void			md5_64_oper(t_ssl *h, int i);
void			md5_buffer_oper(t_ssl *h, int i, uint32_t *words);
uint32_t		*process_chunk_md5(uint32_t *chunk, t_ssl *h);

/*
** sha256.c
*/

uint32_t		sha256_aux(uint32_t b, uint32_t c, uint32_t d, char funct);
void			sha256_64_oper(t_ssl *h, uint32_t *words);
void			sha256_buffer_oper(t_ssl *h, int i, uint32_t *words);
uint32_t		*process_chunk_sha256(uint32_t *chunk, t_ssl *h);

/*
** rot_32_bits.c
*/

uint32_t		rot_32_left(uint32_t base, uint32_t rounds);
uint32_t		rot_32_right(uint32_t base, uint32_t rounds);

#endif
