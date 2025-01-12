/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:12:25 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/12 01:08:55 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <unistd.h>

//````````````````````````````````PROTOTYPES````````````````````````````````````
int		main(int argc, char *argv[]);
//```````1st: make an appropriate storage for bits.`````````````````````````````
char	**bit_storage_calculator(char *msg);-
//```````2nd: convert string to bits and store them.````````````````````````````
void	**str_to_bits(char *msg, char **bits_storage);
//```````3rd: send bits of message to server by signal.`````````````````````````
void	send_message(int pid, char **bit_storage);

int	main(int argc, char *argv[])
{
	int		pid_of_server;
	int		mem_free_index;
	char	**bit_storage;

	if (argc != 3)
	{
		ft_printf("Please input only two parameters!\n \
				   1. Server's PID (ex.41614) 2. A message (ex.\"Hello\"\n");
		return (1);
	}
	pid_of_server = ft_atoi(argv[1]);
	bit_storage = bit_storage_calculator(argv[2]);
	if (!bit_storage)
	{
		ft_printf("Error: Failed to allocate memory for bits storage.\n");
		return (1);
	}
	str_to_bits(argv[2], bit_storage);
	send_message(pid_of_server, bit_storage);
	mem_free_index = 0;
	while (bit_storage[mem_free_index])
		free(bit_storage[mem_free_index++]);
	free(bit_storage);
	return (0);
}

char	**bit_storage_calculator(char *msg)
{
	int		msg_len;
	int		msg_index;
	char	**bits_storage;

	msg_len = ft_strlen(msg);
	bits_storage = malloc((msg_len + 1) * sizeof(char *));
	if (!bits_storage)
		return (NULL);
	msg_index = 0;
	while (msg_index < msg_len)
	{
		bits_storage[msg_index] = malloc(9 * sizeof(char));
		if (!bits_storage[msg_index])
		{
			while (msg_index > 0)
				free(bits_storage[--msg_index]);
			free(bits_storage);
			return (NULL);
		}
		msg_index++;
	}
	bits_storage[msg_len] = NULL;
	return (bits_storage);
}

void	**str_to_bits(char *msg, char **bits_storage)
{
	int		str_index;
	int		bit_index;
	int		char_in_ascii;

	str_index = 0;
	while (msg[str_index])
	{
		char_in_ascii = msg[str_index];
		bit_index = 7;
		while (bit_index >= 0)
		{
			if (char_in_ascii & (1 << bit_index))
				bits_storage[str_index][7 - bit_index] = '1';
			else
				bits_storage[str_index][7 - bit_index] = '0';
			bit_index--;
		}
		bits_storage[str_index][8] = '\0';
		str_index++;
	}
}

void	send_message(int pid, char **bit_storage)
{
	int	str_index;
	int	bit_index;

	str_index = 0;
	while (bit_storage[str_index])
	{
		bit_index = 0;
		while (bit_storage[str_index][bit_index])
		{
			if (bit_storage[str_index][bit_index] == '0')
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit_index++;
			usleep(100);
		}
		str_index++;
		bit_index = 0;
		while (bit_index < 8)
		{
			kill(pid, SIGUSR1);
			bit_index++;
			usleep(100);
		}
	}
}


