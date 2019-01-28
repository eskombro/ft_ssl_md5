/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 20:43:00 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/28 12:39:51 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

/*
** This step uses a 64-element table T[1 ... 64] constructed from the
** sine function. Let T[i] denote the i-th element of the table, which
** is equal to the integer part of 4294967296 times abs(sin(i)), where i
** is in radians.
*/

const uint32_t g_const_md5[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
	0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
	0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
	0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
	0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
	0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

const uint32_t g_rotation_rounds[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12,
	17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9,
	14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6,
	10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static uint32_t	md5_aux(uint32_t b, uint32_t c, uint32_t d, char funct)
{
	if (funct == 'F')
		return ((b & c) | (~b & d));
	else if (funct == 'G')
		return ((b & d) | (c & ~d));
	else if (funct == 'H')
		return (b ^ c ^ d);
	else if (funct == 'I')
		return (c ^ (b | ~d));
	return (0);
}

static void		invert_bytes_md5(uint32_t *words, t_ssl *h)
{
	int			i;

	i = -1;
	h->chunk_current++;
	if (h->chunk_current == h->chunk_tt)
	{
		while (++i < 4)
		{
			*words = (*words & 0x000000FF) << 24 | (*words & 0x0000FF00) << 8 |
				(*words & 0x00FF0000) >> 8 | (*words & 0xFF000000) >> 24;
			words++;
		}
	}
}

static void		md5_64_oper(t_ssl *h, int i)
{
	if (i < 16)
	{
		h->f = md5_aux(h->temp_b[1], h->temp_b[2], h->temp_b[3], 'F');
		h->g = i;
	}
	else if (i < 32)
	{
		h->f = md5_aux(h->temp_b[1], h->temp_b[2], h->temp_b[3], 'G');
		h->g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		h->f = md5_aux(h->temp_b[1], h->temp_b[2], h->temp_b[3], 'H');
		h->g = (3 * i + 5) % 16;
	}
	else
	{
		h->f = md5_aux(h->temp_b[1], h->temp_b[2], h->temp_b[3], 'I');
		h->g = (7 * i) % 16;
	}
}

static void		md5_buffer_oper(t_ssl *h, int i, uint32_t *words)
{
	uint32_t	tmp;
	uint32_t	to_rotate;

	tmp = h->temp_b[3];
	h->temp_b[3] = h->temp_b[2];
	h->temp_b[2] = h->temp_b[1];
	to_rotate = h->temp_b[0] + h->f + g_const_md5[i] + words[h->g];
	h->temp_b[1] += rot_32_left(to_rotate, g_rotation_rounds[i]);
	h->temp_b[0] = tmp;
}

uint32_t		*process_chunk_md5(uint32_t *chunk, t_ssl *h)
{
	uint32_t	*words;
	int			i;

	if (!(words = (uint32_t *)ft_memalloc(sizeof(uint32_t) * 16)))
		return (NULL);
	i = -1;
	while (++i < 16)
		ft_memcpy(&words[i], chunk + i, 4);
	ft_memcpy(h->temp_b, h->md_buff, 32);
	i = -1;
	while (++i < 64)
	{
		md5_64_oper(h, i);
		md5_buffer_oper(h, i, words);
	}
	i = -1;
	while (++i < 4)
		h->md_buff[i] += h->temp_b[i];
	invert_bytes_md5(h->md_buff, h);
	free(words);
	return (h->md_buff);
}
