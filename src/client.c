/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:43:08 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/22 19:12:00 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	send_char_as_bits(pid_t server_pid, char character, int bit_position)
{
	if (bit_position < 8)
	{
		if ((character >> bit_position) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(700);
		send_char_as_bits(server_pid, character, bit_position + 1);
	}
}

void	iterate_string(pid_t server_pid, char *str)
{
	if (*str)
	{
		send_char_as_bits(server_pid, *str, 0);
		iterate_string(server_pid, str + 1);
	}
	else
		send_char_as_bits(server_pid, '\0', 0);
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
	{
		ft_putstr("Usage: ./client [server_pid] [message]\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_putstr("Error: Invalid server PID\n");
		return (1);
	}
	iterate_string(server_pid, argv[2]);
	return (0);
}
