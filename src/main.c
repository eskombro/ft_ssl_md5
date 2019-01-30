/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:13 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/30 21:41:04 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

t_alg			g_alg[] = {
	{"md5", 4, &process_chunk_md5, &initialize_buff_md5},
	{"sha256", 8, &process_chunk_sha2, &initialize_buff_sha256},
	{"sha224", 7, &process_chunk_sha2, &initialize_buff_sha224}
};

static int		read_file(t_ssl *h, int fd)
{
	char		*line;
	int			r;

	h->f_txt[h->f_cur] = NULL;
	if (!(line = ft_memalloc(BUFF_SIZE_READ)))
		return (1);
	while ((r = read(fd, line, BUFF_SIZE_READ)))
	{
		if (h->f_txt[h->f_cur] == NULL)
			h->f_txt[h->f_cur] = ft_strdup(line);
		else
			h->f_txt[h->f_cur] = ft_strjoin_free(h->f_txt[h->f_cur], line, 0);
		ft_bzero(line, BUFF_SIZE_READ);
	}
	ft_strdel(&line);
	if (!h->f_txt[h->f_cur])
		h->f_txt[h->f_cur] = ft_strnew(1);
	return (0);
}

static int		main_logic(t_ssl *h)
{
	int			response;
	int			fd;

	response = 1;
	h->chunk_current = 0;
	if ((h->md_buff = g_alg[h->algo - 1].init_buff(h->b_size)))
	{
		fd = 0;
		if (h->std_in == 0)
			fd = open(h->f_path[h->f_cur], O_RDWR);
		if (fd >= 0 || h->options & OPT_S)
		{
			if (!(h->options & OPT_S))
				read_file(h, fd);
			response = launch_algo(h->f_txt[h->f_cur], h);
			ft_strdel(&h->f_txt[h->f_cur]);
			h->options = h->options & OPT_S ? h->options ^ OPT_S : 0;
		}
		else
			print_message(2, h->f_path[h->f_cur]);
		free(h->md_buff);
	}
	return (response);
}

int				main(int ac, char **av)
{
	t_ssl		*h;

	if (ac == 1)
	{
		print_message(1, NULL);
		return (1);
	}
	h = (t_ssl*)ft_memalloc(sizeof(t_ssl));
	if (!h || handle_args(h, ac, av))
		return (1);
	h->f_cur = -1;
	while (++h->f_cur < h->file_ct)
	{
		if (main_logic(h))
			return (1);
		h->std_in = 0;
	}
	ft_strdel(&h->algo_name);
	while (h->file_ct)
		ft_strdel(&h->f_path[h->file_ct-- - 1]);
	return (0);
}
