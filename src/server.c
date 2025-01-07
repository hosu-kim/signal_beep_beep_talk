/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:46:18 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/07 01:27:58 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>

// set up a signal handler to use sigaction()
void	signal_setup(void)
{
	struct sigaction	sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = char_converter;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}
/* SIGNAL_SETUP
	sigaction: a date type from signal.h, sa: the name of the structure
	SA_SIGINFO: lets more params than just a signal number.
	sa.sa_sigaction: passes signals to a func
	sigaction(SIGUSR1, &sa, NULL): sets which signal the func takes
--------------------------------------------------------------------------------
*/
// calculates each bit array to character.
char	char_converter(int *bit_array)
{
	int		i;
	char	character;

	character = 0;
	i = 0;
	while (i < BUFFER_SIZE)
	{
		character |= (bit_array[i] << i);
		i++;
	}
	return (character);
}
/* 
CHAR_CONVERTER
	character |= (bit_array[i] << i)
		|=: OR operator, compares each bit, 
		if either bit is a 1,
		assigns 1 to the corresponding bit position in the left operand. 
--------------------------------------------------------------------------------
*/
// prints a string converted from a bit array.
void	msg_printer(char character, char *sg, int *char_index)
{
	if (*char_index >= msg_size - 1)
	{
		msg_size *= 2;
		msg = (char *)
	}
	msg[(*char_index)++] = character;
	if (character == '\0')
	{
		write(1, msg, *char_index - 1);
		write(1, "\n", 1);
		*char_index = 0;
	}
}
/*
--------------------------------------------------------------------------------
*/
void	signal_proccessor(int signal, siginfo_t *info, void *context)
{
	static int	bit_array[BUFFER_SIZE];
	static int	bit_index;
	static char	*msg;
	static int	char_index;
	static int	msg_size;
	char		character;
	
	(void)context;
	msg_size = 1024;
	msg = (char *)malloc(sizeof(char) * msg_size);
	if (msg == NULL)
		exit (1);
	bit_index = 0;
	char_index = 0;
	if (signal == SIGUSR1)
		bit_array[bit_index] = 0;
	else
		bit_array[bit_index] = 1;
	bit_index++;
	if (bit_index == BUFFER_SIZE)
	{
		character = char_converter(bit_array);
		msg_printer(character, msg, &char_index);
		bit_index = 0;
	}
}

int	main(void)
{
	int	pid;

	signal_setup(); // sets up the signal handler
	pid = getpid(); // gets the process id
	ft_printf("\nServer is working. Please provide PID to client.\
			\nPID: %d", pid);
	while (1)
	{
		pause();
	}
	return (0);
}
