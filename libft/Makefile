# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhigelin <dhigelin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 17:25:17 by sjimenez          #+#    #+#              #
#    Updated: 2018/02/26 05:24:31 by sjimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Werror -Wextra

SRCS_DIR = srcs/

SRC = ft_atoi.c			\
	  ft_bzero.c		\
	  ft_isalnum.c		\
	  ft_isalpha.c		\
	  ft_isascii.c		\
	  ft_isdigit.c		\
	  ft_isprint.c		\
	  ft_itoa.c			\
	  ft_memalloc.c		\
	  ft_memccpy.c		\
	  ft_memchr.c		\
	  ft_memcmp.c		\
	  ft_memcpy.c		\
	  ft_memdel.c		\
	  ft_memmove.c		\
	  ft_memset.c		\
	  ft_putchar.c		\
	  ft_putchar_fd.c	\
	  ft_putendl.c		\
	  ft_putendl_fd.c	\
	  ft_putnbr.c		\
	  ft_putnbr_fd.c	\
	  ft_putstr.c		\
	  ft_putstr_fd.c	\
	  ft_strcat.c		\
	  ft_strchr.c		\
	  ft_strclr.c		\
	  ft_strcmp.c		\
	  ft_strcpy.c		\
	  ft_strdel.c		\
	  ft_strdup.c		\
	  ft_strequ.c		\
	  ft_striter.c		\
	  ft_striteri.c		\
	  ft_strjoin.c		\
	  ft_strlcat.c		\
	  ft_strlen.c		\
	  ft_strmap.c		\
	  ft_strmapi.c		\
	  ft_strncat.c		\
	  ft_strncmp.c		\
	  ft_strncpy.c		\
	  ft_strnequ.c		\
	  ft_strnew.c		\
	  ft_strnstr.c		\
	  ft_strrchr.c		\
	  ft_strsplit.c		\
	  ft_strstr.c		\
	  ft_strsub.c		\
	  ft_strtrim.c		\
	  ft_tolower.c		\
	  ft_toupper.c		\
	  ft_lstnew.c		\
	  ft_lstdelone.c	\
	  ft_lstdel.c		\
	  ft_lstadd.c		\
	  ft_lstiter.c		\
	  ft_lstmap.c		\
	  ft_isupper.c		\
	  ft_islower.c		\
	  ft_strjoin_free.c \
	  ft_strrev.c		\
	  ft_sort_tab_int.c	\
	  ft_gnl.c			\
	  ft_maltabtab.c	\
	  ft_print_tabstr.c	\
	  ft_strtrim_free.c	\
	  ft_freetabstr.c	\
	  ft_itoa_base.c	\
	  ft_itoa_long.c	\
	  ft_itoa_base_ulong.c \
	  ft_strtolower.c	\
	  ft_strtoupper.c	\
	  ft_strsub_free.c	\
	  ft_lltoa_base.c	\
	  ft_ulltoa_base.c	\
	  ft_cut_and_join.c	\
	  ft_str_realloc.c	\
	  ft_strrealloc.c	\
	  ft_iterative_power.c	\
	  ft_init_tab_int.c	\
	  ft_asprintf.c		\
	  ft_dprintf.c		\
	  ft_pf_conversion.c\
	  ft_pf_options.c	\
	  ft_pf_parsing.c	\
	  ft_pf_unicode.c	\
	  ft_printf.c		\
	  ft_vprintf.c		\
	  ft_countchar.c	\
	  ft_isstrdigit.c	\
	  ft_atol.c			\
	  ft_isstrnumber.c	\
	  ft_swap.c			\
	  ft_round.c		\

SRC_O = $(addprefix $(SRCS_DIR),  $(SRC:.c=.o))

all: $(NAME)

%.o: %.c
	@gcc -c $(FLAGS) -o $@ $< -I includes/

$(NAME): $(SRC_O)
	@ar rc $(NAME) $(SRC_O)
	@ranlib $(NAME)
	@echo "libft.a created"

clean:
	@rm -Rf $(SRC_O)
	@echo "Libft clean executed"
	
fclean: clean
	@rm -Rf $(NAME)
	@echo "Libft fclean executed"

re: fclean all

.PHONY: re clean fclean all
