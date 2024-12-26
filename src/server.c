/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:38:09 by hoskim            #+#    #+#             */
/*   Updated: 2024/12/26 18:58:18 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

// int	main(void)
// {
// 	int		pid;
// 	char	*msg;

// 	pid = getpid();
// 	printf("Server's PID: %d\n", pid);
// 	while (1)
// 	{
		
// 	}

// 	return (0);
// }

// // sigaction

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	receive_signal(int sig, siginfo_t *info, void *context)
{
	static int	bit_count = 0;
	static char	current_char = 0;
	pid_t		client_pid = info->si_pid;

	(void)context;

	if (sig == SIGUSR1)
		current_char |= (1 << (7 - bit_count));  // Set bit to 1
	else if (sig == SIGUSR2)
		current_char &= ~(1 << (7 - bit_count));  // Set bit to 0

	bit_count++;
	if (bit_count == 8)
	{
		write(1, &current_char, 1);  // Print the received character
		bit_count = 0;
		current_char = 0;
	}
	// Acknowledge the client
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	action;

	action.sa_sigaction = receive_signal;
	action.sa_flags = SA_SIGINFO;

	// Set up signal handlers
	if (sigaction(SIGUSR1, &action, NULL) == -1)
	{
		perror("Error setting SIGUSR1 handler");
		return (1);
	}
	if (sigaction(SIGUSR2, &action, NULL) == -1)
	{
		perror("Error setting SIGUSR2 handler");
		return (1);
	}

	printf("Server is running. PID: %d\n", getpid());
	while (1)
		pause();  // Wait for signals
	return (0);
}
