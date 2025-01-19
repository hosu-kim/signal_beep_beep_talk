/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:14:32 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/19 19:52:18 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	send_char(pid_t server_pid, char c)
{
	int	bit;
	int	bit_index;

	bit_index = 0;
	while (bit_index < 8)
	{
		bit = (c >> bit_index) & 1;
		if (bit == 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(500);
		bit_index++;
	}
}

void	send_string(pid_t server_pid, char *str)
{
	int	char_index;

	char_index = 0;
	while (str[char_index])
	{
		send_char(server_pid, str[char_index]);
		char_index++;
	}
	send_char(server_pid, '\0');
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
	send_string(server_pid, argv[2]);
	return (0);
}
