NAME = minitalk
SERVER = server
CLIENT = client
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS_SERVER = server.c
SECS_CLIENT = client.c
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
HEADER = minitalk.h

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(SERVER)

$(CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(CLIENT)

clean:
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re