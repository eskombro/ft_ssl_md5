/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 03:17:50 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/28 11:08:42 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

static void		print_result(t_ssl *h, int tmp_buff_size)
{
	int			i;

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

int				launch_algo(char *str, t_ssl *h)
{
	int			i;

	i = -1;
	if (!(h->final_str = preproc_str(str, 512, 64, h)))
		return (1);
	if (!(h->temp_b = initialize_md_buff(h->b_size, h->algo)))
		return (1);
	while (++i < h->chunk_tt)
	{
		if (h->algo == MD5)
			h->md_buff = process_chunk_md5(h->final_str + (i * 16), h);
		else if (h->algo == SHA_256)
			h->md_buff = process_chunk_sha256(h->final_str + (i * 16), h);
	}
	print_result(h, h->b_size);
	free(h->final_str);
	free(h->temp_b);
	return (0);
}
