/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debbug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:10 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/14 23:33:43 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

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

void	print_buff_bits(char *buff, uint64_t expect_ct)
{
	uint64_t	i;

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

void	print_debbug(char *buff, uint64_t expect_ct)
{
	int			i;

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
