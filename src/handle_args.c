/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 07:47:30 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/28 10:34:40 by sjimenez         ###   ########.fr       */
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
		return (2);
	}
	return (0);
}

static void		add_quotes_to_path(t_ssl *h)
{
	if (h->options & OPT_S)
	{
		if (!(h->options & OPT_P))
		{
			h->f_txt[0] = ft_strdup(h->f_path[0]);
			h->f_path[0] = ft_strjoin_free("\"", h->f_path[0], 2);
			h->f_path[0] = ft_strjoin_free(h->f_path[0], "\"", 1);
		}
		else
		{
			h->f_txt[1] = ft_strdup(h->f_path[1]);
			h->f_path[1] = ft_strjoin_free("\"", h->f_path[1], 2);
			h->f_path[1] = ft_strjoin_free(h->f_path[1], "\"", 1);
		}
	}
}

static int		handle_options(int ac, char **av, t_ssl *h, int *i)
{
	int			r;

	*i = 1;
	while (++(*i) < ac && h->file_ct == 0)
	{
		if (av[*i][0] == '-')
		{
			r = is_valid_option(h, av[*i]);
			if (!r)
			{
				print_message(4, av[*i]);
				return (1);
			}
			else if (r == 2)
				break ;
		}
		else
		{
			(*i)--;
			break ;
		}
	}
	return (0);
}

int				select_algo(char **av, t_ssl *h)
{
	if (!ft_strcmp(av[1], "md5") || !ft_strcmp(av[1], "sha256"))
		h->algo_name = ft_strdup(av[1]);
	else
	{
		print_message(3, NULL);
		return (1);
	}
	if (!ft_strcmp(h->algo_name, "md5"))
		h->algo = MD5;
	else if (!ft_strcmp(h->algo_name, "sha256"))
		h->algo = SHA_256;
	return (0);
}

int				handle_args(t_ssl *h, int ac, char **av)
{
	int			i;
	int			j;

	h->file_ct = 0;
	if (handle_options(ac, av, h, &i) || select_algo(av, h))
		return (1);
	j = i;
	while (++i < ac)
		h->file_ct++;
	i = -1;
	if (h->file_ct == 0 || h->options & OPT_P)
	{
		h->file_ct++;
		h->std_in = 1;
		i++;
		j--;
	}
	h->f_path = (char**)ft_memalloc(sizeof(char*) * (h->file_ct + 1));
	while (++i < h->file_ct)
		h->f_path[i] = ft_strdup(av[i + j + 1]);
	h->f_txt = (char**)ft_memalloc(sizeof(char*) * (h->file_ct + 1));
	add_quotes_to_path(h);
	if (!h->algo_name || !h->f_path)
		return (1);
	return (0);
}
