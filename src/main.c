/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:13 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/27 06:15:51 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

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

int				handle_args(t_ssl *h, int ac, char **av)
{
	int			i;

	i = 0;
	while (++i < ac)
	{
		if (i == 1)
		{
			if (!(h->algo_name = ft_strdup(av[1])))
				return (1);
			if (!(h->file_path = ft_strdup(av[ac - 1])))
				return (1);
			if (!ft_strcmp(av[1], "md5"))
				h->algo = MD5;
			else if (!ft_strcmp(av[1], "sha256"))
				h->algo = SHA_256;
			else
			{
				ft_printf("Error: possible commands are \"md5\" and \"sha256\"\n");
				exit(1);
			}
		}
		else
		{
			//Handle options
		}
	}
	return (0);
}

int				main(int ac, char **av)
{
	uint32_t	response;
	t_ssl		*h;
	char		*b_size;
	int			fd;

	response = 1;
	if (!(h = (t_ssl*)ft_memalloc(sizeof(t_ssl))))
		return (1);
	if (ac == 1)
		ft_printf("Usage: ./ft_ssl command [command options] [command args]\n");
	else
	{
		if (handle_args(h, ac, av))
			return (1);
		b_size = ft_strdup(TEMP_BUFFERS_SIZE);
		h->b_size = b_size[h->algo - 1] - 48;
		free(b_size);
		if ((h->md_buff = initialize_md_buff(h->b_size, h->algo)))
		{
			if ((fd = open(av[2], O_RDWR)) >= 0)
			{
				read_file(h, fd);
				response = launch_algo(h->file_txt, h);
				free(h->file_txt);
			}
			else
			{
				if (av[2])
				{
					ft_printf("Error: '%s'\n", av[2]);
					ft_printf("File doesn't exist or is a directory\n");
				}
				else
					ft_printf("Usage: ./ft_ssl command [command options] [command args]\n");
			}
		}

	}
	return (response);
}
