/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:14:32 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/21 04:17:37 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

// I will sen
void	send_char(pid_t server_pid, char c, int bit_index)
{
	if (bit_index < 8)
	{
		if ((c >> bit_index) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(100);
		send_char(server_pid, c, bit_index + 1);
	}
}

void	send_string(pid_t server_pid, char *str)
{
	if (*str)
	{
		send_char(server_pid, *str, 0);
		send_string(server_pid, str + 1);
	}
	else
		send_char(server_pid, '\0', 0);
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
