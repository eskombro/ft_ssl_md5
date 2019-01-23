/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:13 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/24 00:44:00 by sjimenez         ###   ########.fr       */
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

int				launch_md5(char *str, t_ssl *h)
{
	int				i;

	i = -1;
	h->final_str = preproc_str(str, 512, 64, h);
	if (!(h->temp_b = initialize_md_buff(4, h->algo)))
		return (1);
	while (++i < h->chunk_tt)
		h->md_buff = process_chunk_md5(h->final_str + (i * 16), h);
	i = -1;
	if (h->md_buff)
		while (++i < 16)
			ft_printf("%2.2x", *((unsigned char *)h->md_buff + i));
	ft_printf("\n");
	free(h->final_str);
	free(h->temp_b);
	return (0);
}

int				launch_sha256(char *str, t_ssl *h)
{
	int				i;

	i = -1;
	h->final_str = preproc_str(str, 512, 64, h);
	if (!(h->temp_b = initialize_md_buff(8, h->algo)))
		return (1);
	while (++i < h->chunk_tt)
		h->md_buff = process_chunk_sha256(h->final_str + (i * 16), h);
	i = -1;
	if (h->md_buff)
		while (++i < 8)
			ft_printf("%2.2x", *(h->md_buff + i));
	free(h->final_str);
	free(h->temp_b);
	return (0);
}

int				main(int argc, char **argv)
{
	uint32_t	response;
	t_ssl		h;
	int			i;
	char		*b_size;

	response = 1;
	i = 0;
	h.algo = 0;
	if (argc == 1)
		ft_printf("Usage: ./ft_ssl command [command options] [command args]\n");
	else
	{
		h.options = 0;
		while (++i < argc)
		{
			if (i == 1)
			{
				if (!ft_strcmp(argv[1], "md5"))
					h.algo = MD5;
				else if (!ft_strcmp(argv[1], "sha256"))
					h.algo = SHA_256;
				else
				{
					ft_printf("Error: possible commands are \"md5\" and \"sha256\"\n");
					exit(1);
				}
			}
			else
			{
				//Handle options
			}
		}
		b_size = ft_strdup(TEMP_BUFFERS_SIZE);
		if ((h.md_buff = initialize_md_buff(b_size[h.algo - 1], h.algo)))
		{
			if (h.algo == MD5)
				response = launch_md5(argv[2], &h);
			else if (h.algo == SHA_256)
				response = launch_sha256(argv[2], &h);
		}
		free(b_size);
	}
	return (response);
}
