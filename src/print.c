/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:10 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/30 21:42:30 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void				print_result(t_ssl *h, int tmp_buff_size)
{
	int				i;

	i = -1;
	if ((h->options & OPT_P) && h->f_cur == 0)
		ft_printf("%s", h->f_txt[h->f_cur]);
	if (!(h->options & OPT_Q) && !(h->options & OPT_R) && !h->std_in)
		ft_printf("%s (%s) = ",
			ft_strtoupper(h->algo_name), h->f_path[h->f_cur]);
	if (h->md_buff)
		while (++i < tmp_buff_size)
			ft_printf("%8.8x", *(h->md_buff + i));
	if (h->options & OPT_R && !(h->options & OPT_Q) && h->std_in != 1)
		ft_printf(" %s", h->f_path[h->f_cur]);
	ft_printf("\n");
}

void				print_message(int m, char *arg)
{
	int				i;

	i = -1;
	if (m == 1)
	{
		ft_printf("Usage: ./ft_ssl command [command options] [command args]\n");
		ft_printf("Possible commands are:\n");
		while (++i < ALG_NUM)
			ft_printf("-> %s\n", g_alg[i].name);
	}
	else if (m == 2)
		ft_printf("Error: '%s'. File doesn't exist.\n", arg);
	else if (m == 3)
	{
		ft_printf("Error: command doesn't exist.\nPossible commands are:\n");
		while (++i < ALG_NUM)
			ft_printf("-> %s\n", g_alg[i].name);
	}
	else if (m == 4)
		ft_printf("Error: %s is not a valid option \n", arg);
}

void				print_bits(unsigned char c)
{
	unsigned char	i;

	i = 0x80;
	while (i)
	{
		ft_putchar(i & c ? '1' : '0');
		i >>= 1;
	}
}

void				print_buff_bits(char *buff, uint64_t expect_ct)
{
	uint64_t		i;

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

void				print_debbug(char *buff, uint64_t expect_ct)
{
	int				i;

	i = -1;
	print_buff_bits(buff, expect_ct);
	ft_printf("\nexpect_ct: %d\nSize malloc: %d\nConverted str: %s\n",
		expect_ct, expect_ct + 64, buff);
	ft_printf("last 64 bits: ");
	while (++i < 8)
	{
		print_bits(buff[(expect_ct / 8) + i]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}
