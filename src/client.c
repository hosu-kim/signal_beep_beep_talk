/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:41:03 by hoskim            #+#    #+#             */
/*   Updated: 2024/12/26 19:49:19 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

char	**cvt_storage_allotator(char *msg)
{
	int		msg_len;
	char	**cvt_storage;

	msg_len = ft_strlen(msg);
	cvt_storage = malloc((msg_len + 1) * sizeof(char *));
	if (!cvt_storage)
		return (NULL);
	while (msg_len > 0)
	{
		cvt_storage[msg_len - 1] = malloc(9 * sizeof(char));
		if (!cvt_storage[msg_len - 1])
		{
			while (msg_len > 0)
			{
				free(cvt_storage[msg_len - 1]);
				msg_len--;
			}
			free (cvt_storage);
			return (NULL);
		}
		msg_len--;
	}
	return (cvt_storage);
}

char	**bit_coverter(char *msg)
{
	int		str_index;
	int		bit_index;
	int		char_in_ascii;
	char	**cvt_storage;

	cvt_storage = cvt_storage_allotator(msg);
	str_index = 0;
	char_in_ascii = 0;
	while (msg[str_index] != '\0')
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
	return (cvt_storage);
}

int	main(int argc, char *argv[])
{
	char	*pid_from_argv;
	char	*msg;
	char	**bit_storage;
	int		pid;
	int		index_in_str;
	int		index_in_bit;

	pid_from_argv = argv[1];
	pid = ft_atoi(pid_from_argv);
	msg = argv[2];
	if (argc != 3)
	{
		printf("Please include only two parameters: 1. Server's PID \
				2. A meassage\n");
		return (1);
	}
	bit_storage = bit_coverter(msg);
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
		}
		index_in_str++;
	}
	while (*bit_storage)
	{
		free(*bit_storage);
		bit_storage++;
	}
	free(bit_storage);
	return (0);
}
