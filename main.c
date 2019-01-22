/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:13 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/22 01:49:11 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

/*
** Buffer initialization:
** md5:		Arbitrary
** sha256:	Taking the first thirty-two bits of the fractional parts of the
** 			square roots of the first eight prime numbers
*/

uint32_t		*initialize_md_buff(int buff_size, char algo)
{
	uint32_t		*buff;

	if (!(buff = (uint32_t *)ft_memalloc(sizeof(uint32_t) * buff_size + 1)))
		return (NULL);
	if (algo == 0)
	{
		buff[0] = 0x67452301;
		buff[1] = 0xefcdab89;
		buff[2] = 0x98badcfe;
		buff[3] = 0x10325476;
	}
	else if (algo == 1)
	{
		// buff[0] = 0x67e6096a;
		// buff[1] = 0x85ae67bb;
		// buff[2] = 0x72f36e3c;
		// buff[3] = 0x3af54fa5;
		// buff[4] = 0x7f520e51;
		// buff[5] = 0x8c68059b;
		// buff[6] = 0xabd9831f;
		// buff[7] = 0x19cde05b;
		buff[0] = 0x6a09e667;
		buff[1] = 0xbb67ae85;
		buff[2] = 0x3c6ef372;
		buff[3] = 0xa54ff53a;
		buff[4] = 0x510e527f;
		buff[5] = 0x9b05688c;
		buff[6] = 0x1f83d9ab;
		buff[7] = 0x5be0cd19;
	}
	return (buff);
}

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

uint32_t		circular_rot_32_left(uint32_t base, uint32_t rounds)
{
	return ((base << rounds) | (base >> (32 - rounds)));
}

uint32_t		circular_rot_32_right(uint32_t base, uint32_t rounds)
{
	return ((base >> rounds) | (base << (32 - rounds)));
}

int				launch_md5(char *str, t_ssl *h)
{
	int				chunk_tt;
	int				i;

	i = -1;
	h->final_str = pre_str(str, &chunk_tt, 512, 64);
	if (!(h->abcd = initialize_md_buff(4, h->algo)))
		return (1);
	while (++i < chunk_tt)
		h->md_buff = process_chunk_md5(h->final_str + (i * 64), h);
	i = -1;
	if (h->md_buff)
		while (++i < 16)
			ft_printf("%2.2x", *((unsigned char *)h->md_buff + i));
	free(h->final_str);
	free(h->abcd);
	return (0);
}

int				launch_sha256(char *str, t_ssl *h)
{
	int				chunk_tt;
	int				i;

	i = -1;
	h->final_str = pre_str(str, &chunk_tt, 512, 64);

	// while (++i < 64)
	// 	print_bits((unsigned char)(h->final_str[i]));
	// ft_printf("\n");
	// i = -1;

	if (!(h->abcd = initialize_md_buff(8, h->algo)))
		return (1);
	while (++i < chunk_tt)
		h->md_buff = process_chunk_sha256(h->final_str + (i * 64), h);
	i = -1;
	if (h->md_buff)
		while (++i < 32)
			ft_printf("%2.2x", *((unsigned char *)h->md_buff + i));
	free(h->final_str);
	free(h->abcd);
	return (0);
}

int				main(int argc, char **argv)
{
	uint32_t	response;
	t_ssl		h;
	char		salgo;

	h.algo = 1;
	response = 1;
	if (argc == 2)
	{
		if (h.algo == 0)
			if ((h.md_buff = initialize_md_buff(4, h.algo)))
				response = launch_md5(argv[1], &h);
		if (h.algo == 1)
			if ((h.md_buff = initialize_md_buff(8, h.algo)))
				response = launch_sha256(argv[1], &h);
	}
	return (response);
}
