# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/12 18:09:13 by hoskim            #+#    #+#              #
#    Updated: 2025/01/12 18:15:39 by hoskim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER=server
CLIENT=client

all: server client

server:
		gcc -Wall -Werror -Wextra server.c ft_atoi.c ft_putnbr_fd.c -o $(SERVER)
client:
		gcc -Wall -Werror -Wextra client.c ft_atoi.c ft_putnbr_fd.c -o $(CLIENT)
clean:
	rm $(SERVER) $(CLIEN)
fclean: clean

re: clean all