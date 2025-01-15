/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 23:03:41 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/15 22:45:08 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (sign * result);
}

static void	send_signal(pid_t pid, char *message)
{
	int		char_index;
	int		bit_index;
	char	result;

	char_index = 0;
	while (message[char_index] != '\0')
	{
		bit_index = 7;
		while (bit_index >= 0)
		{
			result = (message[char_index] >> bit_index) & 1;
			if (result == 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
			bit_index--;
		}
		char_index++;
	}
	bit_index = 7;
	while (bit_index >= 0)
	{
		kill(pid, SIGUSR2);
		usleep(100);
		bit_index--;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid;

	if (argc != 3)
	{
		write(1, "The requested number of arguments was not entered.\n", 50);
		write(1, "Usage: ./clien [PID] [message]\n", 31);
	}
	server_pid = ft_atoi(argv[1]);
	send_signal(server_pid, argv[2]);
	return (0);
}
