/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:13 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/14 23:34:28 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

const uint32_t g_k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,	0xf57c0faf, 0x4787c62a,
	0xa8304613, 0xfd469501,	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,	0xf61e2562, 0xc040b340,
	0x265e5a51, 0xe9b6c7aa,	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,	0xa9e3e905, 0xfcefa3f8,
	0x676f02d9, 0x8d2a4c8a,	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,	0x289b7ec6, 0xeaa127fa,
	0xd4ef3085, 0x04881d05,	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,	0x655b59c3, 0x8f0ccc92,
	0xffeff47d, 0x85845dd1,	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

const uint32_t g_r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21,
	6, 10, 15, 21, 6, 10, 15, 21};

char	*complete_str(char *str, int *chunk_tot)
{
	uint64_t	bit_ct;
	uint64_t	expect_ct;
	char 		*buff;

	bit_ct = (uint64_t)(ft_strlen(str) * 8);
	expect_ct = bit_ct;
	if (bit_ct < 448)
		expect_ct = 448;
	while ((expect_ct + 64) % 512)
		expect_ct++;
	buff = ft_strnew(expect_ct + 64);
	ft_strcpy(buff, str);
	buff[ft_strlen(str)] = (char)(1 << 7);
	ft_memcpy(buff + (expect_ct / 8), &bit_ct, 8);
	*chunk_tot = (expect_ct + 64) / 512;
	// print_debbug(buff, expect_ct);
	return (buff);
}

uint32_t		*initialize_md_buff(int buff_size)
{
	uint32_t		*md_buff;

	if (!(md_buff = (uint32_t *)ft_memalloc(sizeof(uint32_t) * buff_size + 1)))
		return (NULL);
	md_buff[0] = 0x67452301;
	md_buff[1] = 0xefcdab89;
	md_buff[2] = 0x98badcfe;
	md_buff[3] = 0x10325476;
	return (md_buff);
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

uint32_t	circular_bit_rotation(uint32_t x, uint32_t c)
{
	return (((x) << (c)) | ((x) >> (32 - (c))));
}

uint32_t 		*process_chunk(char *chunk, uint32_t *md_buff)
{
	uint32_t		*words;
	int				i;
	uint32_t		*abcd;
	uint32_t		f;
	uint32_t		g;
	uint32_t		tmp;

	// char xx;
	// xx = -1;
	// while (++xx < 64)
	// {
	// 	if (xx % 8 == 0)
	// 		ft_putchar('\n');
	// 	print_bits(*(chunk + xx));
	// 	ft_putchar(' ');
	// }
	// ft_putchar('\n');

	i = -1;
	if (!(words = (uint32_t *)ft_memalloc(sizeof(uint32_t) * 16)))
		return (NULL);
	while (++i < 16)
		ft_memcpy(&words[i], chunk + (i * 4), 4);
	abcd = initialize_md_buff(4);
	abcd[0] = md_buff[0];
	abcd[1] = md_buff[1];
	abcd[2] = md_buff[2];
	abcd[3] = md_buff[3];
	i = -1;
	while (++i < 64)
	{
		if (i < 16)
		{
			f = md5_aux(abcd[1], abcd[2], abcd[3], 'F');
			g = i;
		}
		else if (i < 32)
		{
			f = md5_aux(abcd[1], abcd[2], abcd[3], 'G');
			g = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
			f = md5_aux(abcd[1], abcd[2], abcd[3], 'H');
			g = (3 * i + 5) % 16;
		}
		else
		{
			f = md5_aux(abcd[1], abcd[2], abcd[3], 'I');
			g = (7 * i) % 16;
		}
		tmp = abcd[3];
		abcd[3] = abcd[2];
		abcd[2] = abcd[1];
		abcd[1] += circular_bit_rotation(abcd[0] + f + g_k[i] + words[g], g_r[i]);
		abcd[0] = tmp;
	}
	md_buff[0] += abcd[0];
	md_buff[1] += abcd[1];
	md_buff[2] += abcd[2];
	md_buff[3] += abcd[3];
	return(md_buff);
}

int		launch_md5(char *str)
{
	char			*str_512;
	uint32_t		*md_buff;
	int				chunk_tot;
	int				chunk_ct;
	unsigned char	*md;
	int				i;

	md_buff = NULL;
	i = -1;
	str_512 = complete_str(str, &chunk_tot);
	if ((md_buff = initialize_md_buff(4)))
	{
		chunk_ct = -1;
		while (++chunk_ct < chunk_tot)
		{
			// ft_printf("Chunk offset: %d\n", (chunk_ct * 64));
			md_buff = process_chunk(str_512 + (chunk_ct * 64), md_buff);
		}
		if (md_buff)
		{
			md = (unsigned char *)md_buff;
			while (++i < 16)
				ft_printf("%x", *(md++));
		}
		free(str_512);
		return (1);
	}
	free(str_512);
	return (0);
}

int		main(int argc, char **argv)
{
	int		response;

	response = 1;
	if (argc == 2)
	{
		response = launch_md5(argv[1]);
	}
	return (response);
}
