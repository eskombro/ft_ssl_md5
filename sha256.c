/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 20:43:00 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/22 01:49:09 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

const uint32_t g_k_256[] = {
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
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

uint32_t		sha256_aux(uint32_t b, uint32_t c, uint32_t d, char funct)
{
	if (funct == 'C')
		return ((b & c) ^ (~b & d));
	else if (funct == 'M')
		return ((b & c) ^ (b & d) ^ (c & d));
	return (0);
}

uint32_t		sha256_aux_sig(uint32_t b, char funct)
{
	if (funct == 'b')
		return (circular_rot_32_right(b, 2) ^ circular_rot_32_right(b, 13) ^ circular_rot_32_right(b, 22));
	else if (funct == 'B')
		return (circular_rot_32_right(b, 6) ^ circular_rot_32_right(b, 11) ^ circular_rot_32_right(b, 25));
	else if (funct == 's')
		return (circular_rot_32_right(b, 7) ^ circular_rot_32_right(b, 18) ^ (b >> 3));
	else if (funct == 'S')
		return (circular_rot_32_right(b, 17) ^ circular_rot_32_right(b, 19) ^ (b >> 10));
	return (0);
}

uint32_t		*process_chunk_sha256(char *chunk, t_ssl *h)
{
	uint32_t		*words;
	int				i;
	uint32_t		temp;
	uint32_t		temp2;

	if (!(words = (uint32_t *)ft_memalloc(sizeof(uint32_t) * 64)))
		return (NULL);
	ft_memcpy(words, chunk, 64);
	i = 15;

	ft_printf("%8.8x\n", words[0]);
	ft_printf("%8.8x\n", words[1]);
	ft_printf("%8.8x\n", words[2]);
	ft_printf("%8.8x\n", words[3]);
	ft_printf("%8.8x\n", words[4]);
	ft_printf("%8.8x\n", words[5]);
	ft_printf("%8.8x\n", words[10]);
	ft_printf("%8.8x\n", words[11]);
	ft_printf("%8.8x\n", words[12]);
	ft_printf("%8.8x\n", words[13]);
	ft_printf("%8.8x\n", words[14]);
	ft_printf("%8.8x\n", words[15]);

	while (++i < 64)
	{
		words[i] = sha256_aux_sig(words[i - 2], 'S') + words[i - 7] + sha256_aux_sig(words[i - 15], 's') + words[i - 16];
		// ft_printf("%l8.8x\n", words[i]);
	}
	ft_memcpy(h->abcd, h->md_buff, 32);
	i = -1;
	while (++i < 64)
	{
		temp = h->abcd[7] + sha256_aux_sig(h->abcd[4], 'B') + sha256_aux(h->abcd[4], h->abcd[5], h->abcd[6], 'C') + g_k_256[i] + words[i];
		temp2 = sha256_aux_sig(h->abcd[0], 'b') + sha256_aux(h->abcd[0], h->abcd[1], h->abcd[2], 'M');
		h->abcd[7] = h->abcd[6];
		h->abcd[6] = h->abcd[5];
		h->abcd[5] = h->abcd[4];
		h->abcd[4] = h->abcd[3] + temp;
		h->abcd[3] = h->abcd[2];
		h->abcd[2] = h->abcd[1];
		h->abcd[1] = h->abcd[0];
		h->abcd[0] = temp + temp2;
	}
	i = -1;
	while (++i < 8)
		h->md_buff[i] += h->abcd[i];
	free(words);
	return (h->md_buff);
}
