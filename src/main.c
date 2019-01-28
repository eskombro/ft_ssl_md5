/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:13 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/28 11:43:19 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

int				read_file(t_ssl *h, int fd)
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

int				main_logic(t_ssl *h)
{
	int			response;
	int			fd;

	response = 1;
	h->chunk_current = 0;
	if ((h->md_buff = initialize_md_buff(h->b_size, h->algo)))
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
	char		*b_size;

	if (ac == 1)
	{
		print_message(1, NULL);
		return (1);
	}
	h = (t_ssl*)ft_memalloc(sizeof(t_ssl));
	if (!h || handle_args(h, ac, av))
		return (1);
	b_size = ft_strdup(TEMP_BUFFERS_SIZE);
	h->b_size = b_size[h->algo - 1] - 48;
	ft_strdel(&b_size);
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
