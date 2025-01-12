/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:12:25 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/12 16:03:07 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

//````````````````````````````````PROTOTYPES````````````````````````````````````
//`````main: use sub-functions to send signal and free memory```````````````````
int		main(int argc, char *argv[]);
//`````1st: make an appropriate storage for bits.```````````````````````````````
char	**bit_storage_calculator(char *msg);
//`````2nd: convert string to bits and store them.``````````````````````````````
void	**str_to_bits(char *msg, char **bits_storage);
//`````3rd: send bits of message to server by signal.```````````````````````````
void	send_message(int pid, char **bit_storage);

//______________________________________________________________________________
/**
 * @brief send message to server.
 * @details
 * STEP:
 * 1. bit_sotrage_calculator
 * 2. str_to_bits
 * 3. send_message
 * 4. free memory
 */
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
//______________________________________________________________________________
/**
 * @brief 1st: make an appropriate storage for bits.
 * @details
 * 1. allocate memory in bits_storage for whole message.
 * 2. allocate memory inside bits_storage for each character.
 * 	(these steps are like making a whole folder and sub-folders for each char.)
 * 3. return bits_storage.
 * @note
 * 1. allocate NULL at the end to indicate the end of the array.
 * 	(the same as a string)
 */
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
//______________________________________________________________________________
/**
 * @brief 2nd: break string into bits and store them.
 * @details
 * 1. convert each character into bits.
 * 2. store them in bits_storage.
 */
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
//______________________________________________________________________________
/**
 * @brief 3rd: send bits of message to server by signal.
 * @details
 * 1. send bits of message to server by signal
 * 2. send 00000000 to indicate of the end of message sending.
 */
void	send_message(int pid, char **bit_storage)
{
	int	char_index;
	int	bit_index;

	char_index = 0;
	while (bit_storage[char_index])
	{
		bit_index = 0;
		while (bit_storage[char_index][bit_index])
		{
			if (bit_storage[char_index][bit_index] == '0')
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit_index++;
			usleep(100);
		}
		char_index++;
	}
	bit_index = 0;
	while (bit_index < 8)
	{
		kill(pid, SIGUSR1);
		bit_index++;
		usleep(100);
	}
}
