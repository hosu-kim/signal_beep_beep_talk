# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 17:44:04 by hoskim            #+#    #+#              #
#    Updated: 2025/01/16 17:44:04 by hoskim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minitalk
SERVER		= server
CLIENT		= client
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

SRCS_SERVER	= server.c utils.c
SRCS_CLIENT	= client.c utils.c
OBJS_SERVER	= $(SRCS_SERVER:.c=.o)
OBJS_CLIENT	= $(SRCS_CLIENT:.c=.o)

HEADER		= minitalk.h

all:		$(NAME)

$(NAME):	$(SERVER) $(CLIENT)

$(SERVER):	$(OBJS_SERVER)
			$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(SERVER)

$(CLIENT):	$(OBJS_CLIENT)
			$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(CLIENT)

%.o: %.c	$(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)

fclean:		clean
			$(RM) $(SERVER) $(CLIENT)

re:			fclean all

.PHONY:		all clean fclean re