/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:13 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/27 13:17:56 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void			print_message(int m, char *arg)
{
	if (m == 1)
		ft_printf("Usage: ./ft_ssl command [command options] [command args]\n");
	else if (m == 2)
		ft_printf("Error: '%s'. File doesn't exist.\n", arg);
	else if (m == 3)
		ft_printf("Error: possible commands are \"md5\" and \"sha256\"\n");
	else if (m == 4)
		ft_printf("Error: %s is not a valid option \n", arg);
}

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
	if ((h->md_buff = initialize_md_buff(h->b_size, h->algo)))
	{
		fd = 0;
		if (h->std_in == 0)
			fd = open(h->f_path[h->f_cur], O_RDWR);
		if (fd >= 0)
		{
			read_file(h, fd);
			response = launch_algo(h->f_txt[h->f_cur], h);
			ft_strdel(&h->f_txt[h->f_cur]);
		}
		else if (h->options & OPT_S)
		{
			response = launch_algo(h->f_txt[h->f_cur], h);
			ft_strdel(&h->f_txt[h->f_cur]);
			if (h->options & OPT_S)
				h->options ^= OPT_S;
		}
		else
		{
			print_message(2, h->f_path[h->f_cur]);
			return (0);
		}
	}
	return (response);
}

int				main(int ac, char **av)
{
	t_ssl		*h;
	char		*b_size;
	int			i;

	if (!(h = (t_ssl*)ft_memalloc(sizeof(t_ssl))))
		return (1);
	if (ac == 1)
		print_message(1, NULL);
	else
	{
		if (handle_args(h, ac, av))
			return (1);
		b_size = ft_strdup(TEMP_BUFFERS_SIZE);
		h->b_size = b_size[h->algo - 1] - 48;
		ft_strdel(&b_size);
		i = 0;
		h->f_cur = -1;
		while (++h->f_cur < h->file_ct)
		{
			h->chunk_current = 0;
			if (main_logic(h))
				return (1);
			h->std_in = 0;
		}
	}
	ft_strdel(&h->algo_name);
	i = -1;
	while (++i < h->file_ct)
		ft_strdel(&h->f_path[i]);
	return (0);
}
