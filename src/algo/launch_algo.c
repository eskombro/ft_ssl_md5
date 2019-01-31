/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 03:17:50 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/31 17:53:38 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

int				select_algo(char **av, t_ssl *h)
{
	int			i;

	i = -1;
	h->algo_name = NULL;
	while (++i < ALG_NUM)
	{
		if (!ft_strcmp(av[1], g_alg[i].name))
		{
			h->algo_name = ft_strdup(av[1]);
			h->algo = i + 1;
			h->b_size = g_alg[i].buff_size;
		}
	}
	if (!h->algo_name)
	{
		print_message(3, NULL);
		return (1);
	}
	return (0);
}

int				launch_algo(char *str, t_ssl *h)
{
	int			i;

	i = -1;
	if (!(h->final_str = preproc_str(str, 512, 64, h)))
		return (1);
	if (!(h->temp_b = g_alg[h->algo - 1].init_buff(h->b_size)))
		return (1);
	ft_bzero(h->temp_b, g_alg[h->algo - 1].buff_size);
	while (++i < h->chunk_tt)
		h->md_buff = g_alg[h->algo - 1].f(h->final_str + (i * 16), h);
	print_result(h, h->b_size);
	free(h->final_str);
	free(h->temp_b);
	return (0);
}
