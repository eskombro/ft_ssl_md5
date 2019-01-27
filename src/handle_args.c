/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 07:47:30 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/27 08:25:40 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

int				is_valid_option(t_ssl *h, char *arg)
{
	if (!ft_strcmp(arg, "-p"))
	{
		h->options |= OPT_P;
		return (1);
	}
	if (!ft_strcmp(arg, "-q"))
	{
		h->options |= OPT_Q;
		return (1);
	}
	if (!ft_strcmp(arg, "-r"))
	{
		h->options |= OPT_R;
		return (1);
	}
	if (!ft_strcmp(arg, "-s"))
	{
		h->options |= OPT_S;
		return (1);
	}
	return (0);
}

int				handle_args(t_ssl *h, int ac, char **av)
{
	int			i;
	int			pos_algo;

	i = 0;
	pos_algo = 0;
	while (++i < ac)
		if (!ft_strcmp(av[i], "md5") || !ft_strcmp(av[i], "sha256"))
			pos_algo = i;
	if (!pos_algo)
		print_message(3, NULL);
	i = 0;
	while (++i < pos_algo)
	{
		if (!is_valid_option(h, av[i]))
		{
			print_message(4, av[i]);
			return (1);
		}
	}
	h->algo_name = ft_strdup(av[pos_algo]);
	if (pos_algo == ac - 1)
	{
		h->std_in = 1;
		h->file_path = ft_strdup("");
	}
	else
	{
		h->file_path = ft_strdup(av[ac - 1]);
	}
	if (!h->algo_name || !h->file_path)
		return (1);
	if (!ft_strcmp(h->algo_name, "md5"))
		h->algo = MD5;
	else if (!ft_strcmp(h->algo_name, "sha256"))
		h->algo = SHA_256;
	return (0);
}
