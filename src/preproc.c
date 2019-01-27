/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preproc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 03:16:12 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/27 03:16:34 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

/*
** Buffer initialization:
**
** md5:		Arbitrary
** sha256:	Taking the first thirty-two bits of the fractional parts of the
** 			square roots of the first eight prime numbers
*/

uint32_t		*initialize_md_buff(int buff_size, char algo)
{
	uint32_t		*buff;

	if (!(buff = (uint32_t *)ft_memalloc(sizeof(uint32_t) * buff_size + 1)))
		return (NULL);
	if (algo == MD5)
	{
		buff[0] = 0x67452301;
		buff[1] = 0xefcdab89;
		buff[2] = 0x98badcfe;
		buff[3] = 0x10325476;
	}
	else if (algo == SHA_256)
	{
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

uint32_t		*preproc_str(char *str, int block_size, int end_size, t_ssl *h)
{
	uint64_t	bit_ct;
	uint64_t	expect_ct;
	uint32_t	*buff;

	bit_ct = (uint64_t)(ft_strlen(str) * 8);
	expect_ct = bit_ct;
	if (bit_ct < (uint64_t)(block_size - end_size))
		expect_ct = (block_size - end_size);
	while ((expect_ct + end_size) % block_size)
		expect_ct++;
	buff = (uint32_t*)ft_memalloc(expect_ct + end_size);
	ft_memcpy(buff, str, ft_strlen(str));
	*((char*)buff + ft_strlen(str)) = (char)(1 << 7);
	ft_memcpy(buff + (expect_ct / 32), &bit_ct, 8);
	h->chunk_tt = (expect_ct + end_size) / block_size;
	return (buff);
}
