/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:41:03 by hoskim            #+#    #+#             */
/*   Updated: 2024/12/28 21:20:15 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

char	**cvt_storage_allotator(char *msg)
{
	int		msg_len;
	int		i;
	char	**cvt_storage;

	msg_len = ft_strlen(msg);
	cvt_storage = malloc((msg_len + 1) * sizeof(char *));
	if (!cvt_storage)
		return (NULL);
	i = 0;
	while (i < msg_len)
	{
		cvt_storage[i] = malloc(9 * sizeof(char));
		if (!cvt_storage[i])
		{
			while (i > 0)
				free(cvt_storage[--i]);
			free (cvt_storage);
			return (NULL);
		}
		i++;
	}
	cvt_storage[msg_len] = NULL;
	return (cvt_storage);
}

void	**convert_to_bits(char *msg, char **cvt_storage)
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
				cvt_storage[str_index][7 - bit_index] = '1';
			else
				cvt_storage[str_index][7 - bit_index] = '0';
			bit_index--;
		}
		cvt_storage[str_index][8] = '\0';
		str_index++;
	}
}

void	send_message(int pid, char **bit_storage)
{
	int	index_in_str;
	int	index_in_bit;

	index_in_str = 0;
	while (bit_storage[index_in_str])
	{
		index_in_bit = 0;
		while (bit_storage[index_in_str][index_in_bit])
		{
			if (bit_storage[index_in_str][index_in_bit] == '1')
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			index_in_bit++;
			usleep(100);
		}
		index_in_str++;
	}
}

int	main(int argc, char *argv[])
{
	int		pid;
	int		index_in_str;
	char	**bit_storage;
	
	if (argc != 3)
	{
		printf("Please include only two parameters: 1. Server's PID 2. A message\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	bit_storage = cvt_storage_allotator(argv[2]);
	if (!bit_storage)
		return (1);

	convert_to_bits(argv[2], bit_storage);
	send_message(pid, bit_storage);

	index_in_str = 0;
	while (bit_storage[index_in_str])
		free(bit_storage[index_in_str++]);
	free(bit_storage);
	return (0);
}