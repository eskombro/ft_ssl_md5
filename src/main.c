/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:13 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/27 08:30:03 by sjimenez         ###   ########.fr       */
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

	h->file_txt = NULL;
	if (!(line = ft_memalloc(BUFF_SIZE_READ)))
		return (1);
	while ((r = read(fd, line, BUFF_SIZE_READ)))
	{
		if (h->file_txt == NULL)
			h->file_txt = ft_strdup(line);
		else
			h->file_txt = ft_strjoin_free(h->file_txt, line, 0);
		ft_bzero(line, BUFF_SIZE_READ);
	}
	ft_strdel(&line);
	if (!h->file_txt)
		h->file_txt = ft_strnew(1);
	return (0);
}

int				main_logic(t_ssl *h, int ac, char **av)
{
	int			response;
	int			fd;

	response = 1;
	if ((h->md_buff = initialize_md_buff(h->b_size, h->algo)))
	{
		fd = 0;
		if (h->std_in == 0)
			fd = open(av[ac - 1], O_RDWR);
		if (fd >= 0)
		{
			read_file(h, fd);
			response = launch_algo(h->file_txt, h);
			ft_strdel(&h->file_txt);
		}
		else
		{
			print_message(2, h->file_path);
		}
	}
	return (response);
}

int				main(int ac, char **av)
{
	t_ssl		*h;
	char		*b_size;

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
		if (main_logic(h, ac, av))
			return (1);
	}
	ft_strdel(&h->algo_name);
	ft_strdel(&h->file_path);
	return (0);
}
