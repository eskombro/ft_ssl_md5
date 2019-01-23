/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:06 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/24 00:29:29 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# define TEMP_BUFFERS_SIZE "48"

# include "libft.h"

enum {OPT_S = 8, OPT_R = 4, OPT_Q = 2, OPT_P = 1};
enum {SHA_256 = 2, MD5 = 1};

typedef struct	s_ssl
{
	char		algo;
	uint32_t	*md_buff;
	uint32_t	*temp_b;
	uint32_t	*final_str;
	uint32_t	*final_str_uint;
	uint32_t	g;
	uint32_t	f;
	int			chunk_tt;
	int			chunk_current;
	char		options;
}				t_ssl;

/*
** main.c
*/

uint32_t		*initialize_md_buff(int buff_size, char algo);
int				launch_md5(char *str, t_ssl *h);
int				launch_sha256(char *str, t_ssl *h);
uint32_t		*preproc_str(char *str, int block_size, int end_size, t_ssl *h);
uint32_t		*initialize_md_buff(int buff_size, char algo);

/*
** md5.c
*/

uint32_t		*process_chunk_md5(uint32_t *chunk, t_ssl *h);

/*
** sha256.c
*/

uint32_t		*process_chunk_sha256(uint32_t *chunk, t_ssl *h);

/*
** rot_32_bits.c
*/

uint32_t		rot_32_left(uint32_t base, uint32_t rounds);
uint32_t		rot_32_right(uint32_t base, uint32_t rounds);

/*
** print_debbug.c
*/

void			print_bits(unsigned char c);
void			print_buff_bits(char *buff, uint64_t expect_ct);
void			print_debbug(char *buff, uint64_t expect_ct);

#endif
