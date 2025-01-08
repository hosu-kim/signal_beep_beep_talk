/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:46:18 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/08 20:02:08 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>

// set up a signal handler to use sigaction()
void	signal_setup(void)
{
	struct sigaction	sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_proccessor;
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
		character |= (bit_array[i] & 1 << i);
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
	...& 1 <<...: to prevent a case that bit_array[i] is not 0 or 1.
--------------------------------------------------------------------------------
*/
// 
static void	allocate_memory(char **msg, int *msg_size, int *char_index)
{
	*msg_size = 1024;
	*msg = (char *)malloc(sizeof(char) * (*msg_size));
	if (*msg == NULL)
	{
		exit(1);
	}
}
/*
--------------------------------------------------------------------------------
*/
static void	resize_buffer(char **msg, int *msg_size, int *char_index)
{
	char	*new_msg;
	int		new_msg_size;
	int		i;
	
	new_msg_size = *msg_size * 2;
	new_msg = (char *)malloc(sizeof(char) * new_msg_size);
	if (new_msg == NULL)
	{
		ft_printf("Error: Memory allocation failed in resize_buffer\n");
		exit(1);
	}
	i = 0;
	while (i < *char_index)
	{
		new_msg[i] = (*msg)[i];
		i++;
	}
	free(*msg);
	*msg = new_msg;
	*msg_size = new_msg_size;
}
/*
--------------------------------------------------------------------------------
*/
static void	append_char(char **msg, int *char_index, char character)
{
	(*msg)[(*char_index)++] = character;
}
/*
--------------------------------------------------------------------------------
*/
static void	print_message(char **msg, int *char_index, siginfo_t *info)
{
	if (*char_index > 1 && (*msg)[*char_index -2] == '\n')
		ft_printf("%.*s", *char_index - 1, *msg);
	else
		ft_printf("%.*s\n", *char_index - 1, *msg);
	*char_index = 0;
	kill(info->si_pid, SIGUSR1);
}
/*
--------------------------------------------------------------------------------
*/
void	process_char(char character, siginfo_t *info)
{
	static char	*msg;
	static int	char_index;
	static int	msg_size;
	
	msg = NULL;
	if (msg == NULL)
		allocate_memory(&msg, &msg_size, &char_index);
	if (char_index + 1 >= msg_size)
		resize_buffer(&msg, &msg_size, &char_index);
	append_char(&msg, &char_index, character);
	if (character == '\0')
		print_message(&msg, &char_index, info);
}
/*
--------------------------------------------------------------------------------
*/
void	signal_proccessor(int signal, siginfo_t *info, void *context)
{
	static int	bit_array[BUFFER_SIZE];
	static int	bit_index;
	char		character;
	int			i;

	(void)context;

	bit_index = 0;
	i = 0;
	while (i < BUFFER_SIZE)
		bit_array[i++] = 0;
	if (signal == SIGUSR1)
		bit_array[bit_index++] = 0;
	else
		bit_array[bit_index++] = 1;
	if (bit_index == BUFFER_SIZE)
	{
		character = char_converter(bit_array);
		process_char(character, info);
	}
}

int	main(void)
{
	int	pid;

	signal_setup();
	pid = getpid(); // gets the process id
	ft_printf("\nServer is working. Please provide PID to client.\
			\nPID: %d\n", pid);
	while (1)
		pause();
	return (0);
}
