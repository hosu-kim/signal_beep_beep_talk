/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:46:18 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/12 14:06:07 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>

static char *g_msg_storage = NULL;

// CONTENTS
int main(void);
//______________________________________________________________________________________
//
void signal_setup(void);
//______________________________________________________________________________________
/*			(2) processes SIGUSR1 and SIGSUR2 signals
				with helper functions. Using: (3), (4)*/
void signal_proccessor(int signal, siginfo_t *info, void *context);
//______________________________________________________________________________________
//			(3) calculates each bit array as a character.
char bits_to_char(int *one_bit_array);
//______________________________________________________________________________________
/*			(4) handles provided characters(combining them to a str, printing...)
				using: (5)-(8)*/
void char_to_str(char character, siginfo_t *info);
//______________________________________________________________________________________
//			(5) allocates required memory on msg_storage to store a received message.
static void allocate_memory(int *msg_size);
//______________________________________________________________________________________
//			(6) double memory allocation if needed.
static void resize_storage(int *msg_size, int *char_index);
//______________________________________________________________________________________
//			(7) append characters to the array storage.
static void char_to_storage(int *char_index, char character);
//______________________________________________________________________________________
//			(8) prints a string on the console.
static void print_message(int *char_index, siginfo_t *info);
//______________________________________________________________________________________
//			(9) memory deallocation in g_msg_storage.
void handle_exit(int signal);

// MAIN__________________________________________________________________________________
/**
 * @details
 *
 */
int main(void)
{
	int pid;

	signal_setup();
	signal(SIGINT, handle_exit);
	signal(SIGTERM, handle_exit);
	pid = getpid();
	ft_printf("\n\nServer is working. Please provide PID to client.\
			\nPID: %d\n\n\n",
			  pid);
	while (1)
		pause();
	return (0);
}
//(1) SIGNAL_SETUP_________________________________________________________________
/**
 * @brief sets up a signal handler to use sigaction().
 *
 * @details
 * 1. sigaction: a data type from signal.h, sa: the name of the structure
 * 2. SA_SIGINFO: sets more params than just one signal number.
 * 3. sa.sa_sigaction: passes signals to a func.
 * 4. sigaction(SIGUSR1, &sa, NULL): sets which signal the func takes.
 */
void signal_setup(void)
{
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_proccessor;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

//(2) SIGNAL_PROCCESSOR________________________________________________________________
/**
 * @brief processes SIGUSR1 and SIGSUR2 signals to
 * 1. becomes sigaction by signal_setup.
 * 2. when it reads 0 and 1 until the maximum bit position(ex.0010101'0'),
 *    sends 'read_char_bits' to 'bits_char_converter'.
 */
void signal_proccessor(int signal, siginfo_t *info, void *context)
{
	static int read_char_bits[MAX_BIT_POSITION];
	static int bit_index;
	char character;

	(void)context;

	if (signal == SIGUSR1)
		read_char_bits[bit_index] = 1;
	else
		read_char_bits[bit_index] = 0;
	bit_index++;
	if (bit_index == MAX_BIT_POSITION)
	{
		character = bits_to_char(read_char_bits);
		char_to_str(character, info);
		bit_index = 0;
	}
}

/*(3) BITS_TO_CHAR____________________________________________________________________
	1. calculates each bit array as a character.
	2. character |= (bit_array[i] << i)
		a. |=: OR operator; compares each bit.
			If either side has 1,
			assigns 1 to the corresponding bit position in the left operand.
		b. ...& 1: to prevent a case that bit_array[i] is not 0 or 1.
*/
char bits_to_char(int *one_bit_array)
{
	int i;
	char as_character;

	as_character = 0;
	i = 0;
	while (i < MAX_BIT_POSITION)
	{
		if (one_bit_array[i])
			as_character |= (1 << i);
		i++;
	}
	return (as_character);
}

/*(4) CHAR_TO_STR____________________________________________________________________
1. handles a provided character */
void char_to_str(char character, siginfo_t *info)
{
	static int char_index;
	static int msg_size;

	if (g_msg_storage == NULL)
		allocate_memory(&msg_size);
	if (char_index + 1 >= msg_size)
		resize_storage(&msg_size, &char_index);
	char_to_storage(&char_index, character);
	if (character == '\0')
		print_message(&char_index, info);
}

/*(5) ALLOCATE_MEMORY________________________________________________________________
allocates required memory on msg_storage to store a received message.*/
static void allocate_memory(int *msg_size)
{
	*msg_size = 1024;
	g_msg_storage = (char *)malloc(sizeof(char) * (*msg_size));
	if (g_msg_storage == NULL)
	{
		ft_printf("Error: Memory allocation failed in allocate_memory().\n");
		exit(1);
	}
}

/*
______________________________________________________________________________*/
static void resize_storage(int *msg_size, int *char_index)
{
	char *new_msg_storage;
	int new_msg_size;
	int i;

	new_msg_size = *msg_size * 2;
	new_msg_storage = (char *)malloc(sizeof(char) * new_msg_size);
	if (new_msg_storage == NULL)
	{
		ft_printf("Error: Memory allocation failed in resize_storage\n");
		exit(1);
	}
	i = 0;
	while (i < *char_index)
	{
		new_msg_storage[i] = (g_msg_storage)[i];
		i++;
	}
	free(g_msg_storage);
	g_msg_storage = new_msg_storage;
	*msg_size = new_msg_size;
}
/*
______________________________________________________________________________*/
static void char_to_storage(int *char_index, char character)
{
	g_msg_storage[(*char_index)++] = character;
}
/*
______________________________________________________________________________*/
static void print_message(int *char_index, siginfo_t *info)
{
	if (char_index > 0)
	{
		if (*char_index > 1 && g_msg_storage[*char_index - 2] == '\n')
			ft_printf("%.*s", *char_index - 1, g_msg_storage);
		else
			ft_printf("%.*s\n", *char_index - 1, g_msg_storage);
	}
	*char_index = 0;
	kill(info->si_pid, SIGUSR1);
}
/*HANDLE_EXIT___________________________________________________________________________
 */
void handle_exit(int signal)
{
	if (g_msg_storage != NULL)
	{
		free(g_msg_storage);
		g_msg_storage = NULL;
	}
	exit(0);
}
