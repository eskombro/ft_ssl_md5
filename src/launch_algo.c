/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 03:17:50 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/27 03:22:33 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

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
