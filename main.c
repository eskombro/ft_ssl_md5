# include "libft.h"

const uint32_t g_k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};


const uint32_t g_r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16,
	23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21};

void	print_bits(unsigned char c)
{
	unsigned char	i;

	i = 0x80;
	while (i)
	{
		ft_putchar(i & c ? '1' : '0');
		i >>= 1;
	}
}

void print_buff_bits(char *buff, uint64_t expect_ct)
{
	uint64_t i;

	i = 0;
	ft_printf("\nBuffer at %p:\n", buff);
	while (i * 8 < expect_ct + 64)
	{
		print_bits(buff[i]);
		ft_putchar(' ');
		i++;
		if (i % 8 == 0)
		 	ft_printf("\n");
	}
}

void print_debbug(char *buff, uint64_t expect_ct)
{
	print_buff_bits(buff, expect_ct);
	ft_printf("\nexpect_ct: %d\nSize malloc: %d\nConverted str: %s\n", expect_ct, expect_ct + 64, buff);
	ft_printf("last 64 bits: ");
	int i;
	i = -1;
	while (++i < 8)
	{
		print_bits(buff[(expect_ct / 8) + i]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}

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
	print_debbug(buff, expect_ct);
	return (buff);
}

uint32_t		*initialize_md_buff(int buff_size)
{
	uint32_t		*md_buff;

	if (!(md_buff = (uint32_t *)ft_memalloc(sizeof(uint32_t) * buff_size + 1)))
		return (NULL);
	md_buff[0] = 0x01234567;
	md_buff[1] = 0x89abcdef;
	md_buff[2] = 0xfedcba98;
	md_buff[3] = 0x76543210;
	return (md_buff);
}

uint32_t		md5_aux(uint32_t x, uint32_t y, uint32_t z, char funct)
{
	if (funct == 'F')
		return ((x & y) | ((!x) & z));
	else if (funct == 'G')
		return ((x & z) | (y & (!z)));
	else if (funct == 'H')
		return (x ^ y ^ z);
	else if (funct == 'I')
		return (y ^ (x | (!z)));
	return (0);
}

void	process_chunk(char *chunk)
{
	uint32_t	*words;
	int			i;

	i = -1;
	if (!(words = (uint32_t *)ft_memalloc(sizeof(uint32_t) * 16)))
		return ;
	while (++i < 16)
		words[i] = *(chunk + (i * 4));
}

int		launch_md5(char *str)
{
	char		*str_512;
	uint32_t	*md_buff;
	int			chunk_tot;
	int			chunk_ct;

	md_buff = NULL;
	chunk_ct = -1;
	str_512 = complete_str(str, &chunk_tot);
	if ((md_buff = initialize_md_buff(4)))
	{
		// Buffers are initialized and ready to operate
		while(++chunk_ct < chunk_tot)
		{
			// Treat every 512 bites chunk
			process_chunk(str_512 + (chunk_ct * 512));
		}
		free(str_512);
		return (1);
	}
	free(str_512);
	return(0);
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
