/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 03:17:50 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/27 04:54:00 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

int				algo_buff_size(int algo)
{
	char			*b;
	int				size;

	if (!(b = ft_strdup(TEMP_BUFFERS_SIZE)))
		return (-1);
	size = b[algo - 1] - 48;
	free(b);
	return (size);
}

int				launch_algo(char *str, t_ssl *h)
{
	int				i;
	int				tmp_buff_size;

	i = -1;
	if ((tmp_buff_size = algo_buff_size(h->algo)) == -1)
		return (1);
	h->final_str = preproc_str(str, 512, 64, h);
	if (!(h->temp_b = initialize_md_buff(tmp_buff_size, h->algo)))
		return (1);
	while (++i < h->chunk_tt)
	{
		if (h->algo == MD5)
			h->md_buff = process_chunk_md5(h->final_str + (i * 16), h);
		else if (h->algo == SHA_256)
			h->md_buff = process_chunk_sha256(h->final_str + (i * 16), h);
	}
	i = -1;
	if (h->md_buff)
		while (++i < tmp_buff_size)
			ft_printf("%8.8x", *(h->md_buff + i));
	ft_printf("\n");
	free(h->final_str);
	free(h->temp_b);
	return (0);
}
