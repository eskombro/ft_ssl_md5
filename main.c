/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:13 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/15 01:46:29 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

const uint32_t g_k[] = {
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
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

const uint32_t g_r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21,
	6, 10, 15, 21, 6, 10, 15, 21};

char			*pre_str(char *str, int *chunk_tt, int block_size, int end_size)
{
	uint64_t	bit_ct;
	uint64_t	expect_ct;
	char		*buff;

	bit_ct = (uint64_t)(ft_strlen(str) * 8);
	expect_ct = bit_ct;
	if (bit_ct < (uint64_t)(block_size - end_size))
		expect_ct = (block_size - end_size);
	while ((expect_ct + end_size) % block_size)
		expect_ct++;
	buff = ft_strnew(expect_ct + end_size);
	ft_strcpy(buff, str);
	buff[ft_strlen(str)] = (char)(1 << 7);
	ft_memcpy(buff + (expect_ct / 8), &bit_ct, 8);
	*chunk_tt = (expect_ct + end_size) / block_size;
	// print_debbug(buff, expect_ct);
	return (buff);
}

uint32_t		*initialize_md_buff(int buff_size)
{
	uint32_t		*buff;

	if (!(buff = (uint32_t *)ft_memalloc(sizeof(uint32_t) * buff_size + 1)))
		return (NULL);
	buff[0] = 0x67452301;
	buff[1] = 0xefcdab89;
	buff[2] = 0x98badcfe;
	buff[3] = 0x10325476;
	return (buff);
}

uint32_t		md5_aux(uint32_t b, uint32_t c, uint32_t d, char funct)
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

uint32_t		circular_rot_32(uint32_t base, uint32_t rounds)
{
	return ((base << rounds) | (base >> (32 - rounds)));
}

void			md5_64_oper(t_ssl *h, int i)
{
	if (i < 16)
	{
		h->f = md5_aux(h->abcd[1], h->abcd[2], h->abcd[3], 'F');
		h->g = i;
	}
	else if (i < 32)
	{
		h->f = md5_aux(h->abcd[1], h->abcd[2], h->abcd[3], 'G');
		h->g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		h->f = md5_aux(h->abcd[1], h->abcd[2], h->abcd[3], 'H');
		h->g = (3 * i + 5) % 16;
	}
	else
	{
		h->f = md5_aux(h->abcd[1], h->abcd[2], h->abcd[3], 'I');
		h->g = (7 * i) % 16;
	}
}

void			md5_buffer_oper(t_ssl *h, int i, uint32_t *words)
{
	uint32_t		tmp;
	uint32_t		to_rotate;

	tmp = h->abcd[3];
	h->abcd[3] = h->abcd[2];
	h->abcd[2] = h->abcd[1];
	to_rotate = h->abcd[0] + h->f + g_k[i] + words[h->g];
	h->abcd[1] += circular_rot_32(to_rotate, g_r[i]);
	h->abcd[0] = tmp;
}

uint32_t		*process_chunk(char *chunk, t_ssl *h)
{
	uint32_t		*words;
	int				i;

	if (!(words = (uint32_t *)ft_memalloc(sizeof(uint32_t) * 16)))
		return (NULL);
	i = -1;
	while (++i < 16)
		ft_memcpy(&words[i], chunk + (i * 4), 4);
	ft_memcpy(h->abcd, h->md_buff, 32);
	i = -1;
	while (++i < 64)
	{
		md5_64_oper(h, i);
		md5_buffer_oper(h, i, words);
	}
	i = -1;
	while (++i < 4)
		h->md_buff[i] += h->abcd[i];
	free(words);
	return (h->md_buff);
}

int				launch_md5(char *str, t_ssl *h)
{
	int				chunk_tt;
	int				i;

	i = -1;
	h->final_str = pre_str(str, &chunk_tt, 512, 64);
	if (!(h->abcd = initialize_md_buff(4)))
		return (1);
	while (++i < chunk_tt)
		h->md_buff = process_chunk(h->final_str + (i * 64), h);
	i = -1;
	if (h->md_buff)
		while (++i < 16)
			ft_printf("%x", *((unsigned char *)h->md_buff + i));
	free(h->final_str);
	free(h->abcd);
	return (0);
}

int				main(int argc, char **argv)
{
	int		response;
	t_ssl	h;

	response = 1;
	if (argc == 2)
	{
		if ((h.md_buff = initialize_md_buff(4)))
			response = launch_md5(argv[1], &h);
	}
	return (response);
}
