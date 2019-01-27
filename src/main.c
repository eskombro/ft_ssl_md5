/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:13 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/27 04:55:45 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

int				main(int ac, char **av)
{
	uint32_t	response;
	t_ssl		h;
	int			i;
	char		*b_size;
	int			fd;
	char		*file_txt;
	char		*line;
	int			r;

	response = 1;
	i = 0;
	h.algo = 0;
	file_txt = NULL;
	line = NULL;
	if (ac == 1)
		ft_printf("Usage: ./ft_ssl command [command options] [command args]\n");
	else
	{
		h.options = 0;
		while (++i < ac)
		{
			if (i == 1)
			{
				if (!ft_strcmp(av[1], "md5"))
					h.algo = MD5;
				else if (!ft_strcmp(av[1], "sha256"))
					h.algo = SHA_256;
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
		b_size = ft_strdup(TEMP_BUFFERS_SIZE);
		if ((h.md_buff = initialize_md_buff(b_size[h.algo - 1], h.algo)))
		{
			if ((fd = open(av[2], O_RDWR)) >= 0)
			{
				line = ft_memalloc(BUFF_SIZE_READ);
				while ((r = read(fd, line, BUFF_SIZE_READ)))
				{
					if (file_txt == NULL)
						file_txt = ft_strdup(line);
					else
						file_txt = ft_strjoin_free(file_txt, line, 0);
					ft_bzero(line, BUFF_SIZE_READ);
				}
				ft_strdel(&line);
				if (!file_txt)
					file_txt = ft_strnew(1);
				response = launch_algo(file_txt, &h);
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
		free(b_size);
	}
	return (response);
}
