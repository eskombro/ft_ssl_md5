/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 20:43:00 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/28 18:24:03 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

/*
** These words represent the first thirty-two bits of the fractional parts of
** the cube roots of the first sixty-four prime numbers
*/

const uint32_t		g_const_sha2[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static uint32_t		sha2_aux(uint32_t b, uint32_t c, uint32_t d, char funct)
{
	if (funct == 'C')
		return ((b & c) ^ (~b & d));
	else if (funct == 'M')
		return ((b & c) ^ (b & d) ^ (c & d));
	return (0);
}

static uint32_t		sha2_aux_sig(uint32_t b, char funct)
{
	if (funct == 'b')
		return (rot_32_right(b, 2) ^ rot_32_right(b, 13) ^ rot_32_right(b, 22));
	else if (funct == 'B')
		return (rot_32_right(b, 6) ^ rot_32_right(b, 11) ^ rot_32_right(b, 25));
	else if (funct == 's')
		return (rot_32_right(b, 7) ^ rot_32_right(b, 18) ^ (b >> 3));
	else if (funct == 'S')
		return (rot_32_right(b, 17) ^ rot_32_right(b, 19) ^ (b >> 10));
	return (0);
}

static void			invert_bytes_sha_2(uint32_t *words, t_ssl *h)
{
	uint32_t		temp_swap;
	uint32_t		*temp_words;
	int				i;
	int				rounds;

	i = -1;
	temp_words = words;
	h->chunk_current++;
	rounds = 16;
	if (h->chunk_current == h->chunk_tt)
		rounds = 14;
	while (++i < rounds)
	{
		*words = (*words & 0x000000FF) << 24 | (*words & 0x0000FF00) << 8 |
			(*words & 0x00FF0000) >> 8 | (*words & 0xFF000000) >> 24;
		words++;
	}
	if (h->chunk_current == h->chunk_tt)
	{
		temp_swap = temp_words[15];
		temp_words[15] = temp_words[14];
		temp_words[14] = temp_swap;
	}
}

static void			sha2_64_oper(t_ssl *h, uint32_t *words)
{
	uint32_t		temp;
	uint32_t		temp2;
	int				i;

	i = -1;
	while (++i < 64)
	{
		temp = h->temp_b[7] + sha2_aux_sig(h->temp_b[4], 'B');
		temp += sha2_aux(h->temp_b[4], h->temp_b[5], h->temp_b[6], 'C');
		temp += g_const_sha2[i] + words[i];
		temp2 = sha2_aux_sig(h->temp_b[0], 'b');
		temp2 += sha2_aux(h->temp_b[0], h->temp_b[1], h->temp_b[2], 'M');
		h->temp_b[7] = h->temp_b[6];
		h->temp_b[6] = h->temp_b[5];
		h->temp_b[5] = h->temp_b[4];
		h->temp_b[4] = h->temp_b[3] + temp;
		h->temp_b[3] = h->temp_b[2];
		h->temp_b[2] = h->temp_b[1];
		h->temp_b[1] = h->temp_b[0];
		h->temp_b[0] = temp + temp2;
	}
}

uint32_t			*process_chunk_sha2(uint32_t *chunk, t_ssl *h)
{
	uint32_t		*words;
	int				i;

	if (!(words = (uint32_t *)ft_memalloc(sizeof(uint32_t) * 64)))
		return (NULL);
	ft_memcpy(words, chunk, 64);
	invert_bytes_sha_2(words, h);
	i = 15;
	while (++i < 64)
	{
		words[i] = sha2_aux_sig(words[i - 2], 'S') + words[i - 7];
		words[i] += sha2_aux_sig(words[i - 15], 's') + words[i - 16];
	}
	ft_memcpy(h->temp_b, h->md_buff, 32);
	sha2_64_oper(h, words);
	i = -1;
	while (++i < 8)
		h->md_buff[i] += h->temp_b[i];
	free(words);
	return (h->md_buff);
}
