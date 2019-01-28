# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjimenez <sjimenez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/23 20:46:59 by sjimenez          #+#    #+#              #
#    Updated: 2019/01/28 11:50:58 by sjimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

FLAGS = -Wall -Werror -Wextra

SRCS_DIR = src/

INCLUDES = include/
LIBFT_INCLUDES = libft/includes

LIB = libft -lft

SRCS =	main.c					\
								\
		algo/md5.c				\
		algo/sha256.c			\
		algo/launch_algo.c		\
								\
		handle_args.c			\
		preproc.c				\
		print.c					\
		rot_32_bits.c			\


SRCS_O = $(addprefix $(SRCS_DIR),  $(SRCS:.c=.o))

ifeq ("$(FLAG)", "SHOW_ALL")
REDIR =
else ifeq ("$(FLAG)", "SHOW_ERROR")
REDIR = 1>/dev/null
else
REDIR = 1>/dev/null 2>/dev/null
endif

ifeq ("$(FLAG2)", "SANITIZE")
SANITIZE = -fsanitize=address -g3
else
SANITIZE =
endif

all: $(NAME)

%.o: %.c
	@gcc -c $(FLAGS) -o $@ $< -I $(INCLUDES) -I $(LIBFT_INCLUDES) $(SANITIZE)

$(NAME): $(SRCS_O) $(SRCS_O_V)
	@echo " \033[0;32m\n------ Compiling Libft -------------\033[0;0m"
	@make -C libft
	@echo " \033[0;32m\n------ Compiling sources -----------\033[0;0m"
	@gcc $(FLAGS) -o $(NAME) $(SRCS_O) -I $(LIBFT_INCLUDES) -L $(LIB) -I $(INCLUDES) $(SANITIZE)
	@echo "Sources compiled"
	@echo " \033[0;32m\n------ ft_ssl_md5 project compiled -\033[0;0m"
	@echo "ft_ssl created"
	@echo " \033[0;32m\n------ Good to go! -----------------\033[0;0m"


clean:
	@echo " \033[0;32m\n------ ft_ssl_md5 clean ------------\033[0;0m"
	@rm -Rf $(SRCS_O)
	@make -C libft clean
	@echo "ft_ssl_md5 clean executed"

fclean: clean
	@echo " \033[0;32m\n------ ft_ssl_md5 fclean -----------\033[0;0m"
	@rm -Rf $(NAME)
	@make -C libft fclean
	@echo "ft_ssl_md5 fclean executed"

clean_libs:
	@rm -Rf $(LIBS_PATH)

re: fclean all

.PHONY: re clean fclean all

.NOTPARALLEL:
