/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 01:42:12 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/18 02:02:31 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	send_char(pid_t server_pid, char c)
{
	int	bit;
	int i;

	i = 0;
	while (i < 8)
	{
		bit = (c >> i) & 1;
		if (bit == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(100);
		i++;
	}
}

void	send_string(pid_t server_pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(server_pid, str[i]);
		i++;
	}
	send_char(server_pid, '\0');
}

int	main(int argc, char **argv)
{
	pid_t server_pid;

	if (argc != 3)
	{
		ft_pitstr("Usage: ./clien [server_pid] [messge]\n");
		return (1);
	}
	server_pid = atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_putstr("Error: Invaild server PID\n");
		return (1);
	}
	send_string(server_pid, argv[2]);
	return (0);
}
