/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:46:18 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/05 23:06:37 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>

# define BUFFER_SIZE 8

void	setup_signals(void)
{
	struct sigaction sa; // the type, sigaction is from signal.h, sa is the name of the structure.
	
	sa.sa_flags = SA_SIGINFO; // let more parameters than just a signal number.
	sa.sa_sigaction = signal_handler; // sets a function to get signals
	sigaction(SIGUSR1, &sa, NULL); // sets which type of signals it provides to the function
	sigaction(SIGUSR2, &sa, NULL);
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int	bit_array[BUFFER_SIZE];
	static int	bit_index;
	static char	msg[1024];
	static int	char_index;
	int			i;
	char		character;

	bit_index = 0;
	char_index = 0;
	(void)context;
	if (signal == SIGUSR1)
		bit_array[bit_index] = 0;
	else
		bit_array[bit_index] = 1;
	bit_index++;
	if (bit_index == BUFFER_SIZE)
	{
		character = 0;
		i = 0;
		while (i < BUFFER_SIZE)
		{
			character |= (bit_array[i] << i);
			i++;
		}
		msg[char_index++] = character;
		if (character == '\0')
		{
			write(1, msg, char_index - 1);
			write(1, "\n", 1);
			char_index = 0;
		}
		bit_index = 0;
	}
}

int	main(void)
{
	int	pid;

	setup_signals();
	pid = getpid();
	ft_printf("\nServer is working. Please provide PID to client.\
			\nPID: %d", pid);
	while (1)
	{
		pause();
	}
	return (0);
}
