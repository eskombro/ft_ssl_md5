/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:40:06 by sjimenez          #+#    #+#             */
/*   Updated: 2019/01/31 18:00:25 by sjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# define BUFF_SIZE_READ 10
# define ALG_NUM 3

# include "libft.h"

enum {OPT_S = 8, OPT_R = 4, OPT_Q = 2, OPT_P = 1};

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
	int			b_size;
	int			file_ct;
	int			f_cur;
	char		options;
	char		*algo_name;
	char		**f_path;
	char		**f_txt;
	char		std_in;
}				t_ssl;

typedef struct	s_alg
{
	char		*name;
	char		buff_size;
	uint32_t	*(*f)(uint32_t *chunk, t_ssl *h);
	uint32_t	*(*init_buff)(int size);
}				t_alg;

t_alg			g_alg[ALG_NUM];

/*
** handle_args.c
*/

int				handle_args(t_ssl *h, int ac, char **av);

/*
** preproc.c
*/

uint32_t		*initialize_buff_md5(int buff_size);
uint32_t		*initialize_buff_sha256(int buff_size);
uint32_t		*initialize_buff_sha224(int buff_size);
uint32_t		*preproc_str(char *str, int block_size, int end_size, t_ssl *h);

/*
** launch_algo.c
*/

int				select_algo(char **av, t_ssl *h);
int				launch_algo(char *str, t_ssl *h);

/*
** md5.c
*/

uint32_t		*process_chunk_md5(uint32_t *chunk, t_ssl *h);

/*
** sha256.c
*/

uint32_t		*process_chunk_sha2(uint32_t *chunk, t_ssl *h);

/*
** rot_32_bits.c
*/

uint32_t		rot_32_left(uint32_t base, uint32_t rounds);
uint32_t		rot_32_right(uint32_t base, uint32_t rounds);

/*
** print.c
*/

void			print_result(t_ssl *h, int tmp_buff_size);
void			print_message(int m, char *arg);
void			print_bits(unsigned char c);
void			print_buff_bits(char *buff, uint64_t expect_ct);
void			print_debbug(char *buff, uint64_t expect_ct);

#endif
