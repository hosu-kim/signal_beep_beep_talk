/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:22:06 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/14 21:10:15 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	pid_printer(pid_t n)
{
	char	c;

	if (n > 9)
	{
		pid_printer((n / 10));
		pid_printer((n % 10));
	}
	else
	{
		c = 48 + n;
		write(1, &c, 1);
	}
}

static void	signal_handler(int signal)
{
	static char	character;
	static int	bit_counter;

	bit_counter++;
	if (signal == SIGUSR1)
		character = character | 1;
	if (bit_counter == 8)
	{
		write(1, &character, 1);
		bit_counter = 0;
		character = 0;
	}
	character = character << 1;
}

int	main(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	write(1, "\nServer is running.\n", 21);
	write(1, "Waiting for message...\n", 24);
	write(1, "-----------------------------------------------------------", 60);
	write(1, "\nServer's PID: ", 16);
	pid_printer(server_pid);
	write(1, "\n", 1);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
	return (0);
}
