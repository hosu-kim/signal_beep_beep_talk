/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:46:18 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/10 23:15:05 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>

static char	*g_msg_storage = NULL;

// CONTENTS
// main function
int			main(void);
//______________________________________________________________________________
// (1) set up a signal handler to use sigaction(), used in main()
void		signal_setup(void);
//______________________________________________________________________________
// (2) processes SIGUSR1 and SIGSUR2 signals with helper functions.
void		signal_proccessor(int signal, siginfo_t *info, void *context);
//______________________________________________________________________________
// (3) calculates each bit array as a character.
char		bits_to_char(int *one_bit_array);
static void	allocate_memory(char **msg_storage, int *msg_size);
// (3) allocates required memory on msg_storage
//	   to store a received message.
static void	resize_storage(char **msg, int *msg_size, int *char_index);
static void	append_char(char **msg, int *char_index, char character);
static void	print_message(char **msg, int *char_index, siginfo_t *info);
void		char_to_str(char character, siginfo_t *info);
/*____________________________________________________________________________
1. getpid(): gets a process id.

STEP
(1) signal_setup
(2) 
1. sigaction: a data type from signal.h, sa: the name of the structure
	2. SA_SIGINFO: sets more params than just one signal number.
	3. sa.sa_sigaction: passes signals to a func.
	4. sigaction(SIGUSR1, &sa, NULL): sets which signal the func takes. */
int	main(void)
{
	int	pid;

	signal_setup();
	signal(SIGINT, handle_exit);
	signal(SIGTERM, handle_exit);
	pid = getpid();
	ft_printf("\nServer is working. Please provide PID to client.\
			\nPID: %d\n", pid);
	while (1)
		pause();
	return (0);
}
/*______________________________________________________________________________
*/
void	signal_setup(void)
{
	struct sigaction	sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_proccessor;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

/*______________________________________________________________________________
1. becomes sigaction by signal_setup.
2. when it reads 0 and 1 until the maximum bit position(ex.0010101'0'),
   sends 'read_char_bits' to 'bits_char_converter'.
*/
void	signal_proccessor(int signal, siginfo_t *info, void *context)
{
	static int	read_char_bits[MAX_BIT_POSITION];
	static int	bit_index;
	char		character;
	int			i;

	(void)context;

	bit_index = 0;
	i = 0;
	while (i < MAX_BIT_POSITION)
		read_char_bits[i++] = 0;
	if (signal == SIGUSR1)
		read_char_bits[bit_index++] = 0;
	else
		read_char_bits[bit_index++] = 1;
	if (bit_index == MAX_BIT_POSITION)
	{
		character = bits_to_char(read_char_bits);
		char_to_str(character, info);
	}
}

//______________________________________________________________________________
/* (2) calculates each bit array as a character.
	1. character |= (bit_array[i] << i)
		a. |=: OR operator; compares each bit. 
			If either side has 1, 
			assigns 1 to the corresponding bit position in the left operand.
		b. ...& 1: to prevent a case that bit_array[i] is not 0 or 1.
*/
char	bits_to_char(int *one_bit_array)
{
	int		i;
	char	as_character;

	as_character = 0;
	i = 0;
	while (i < MAX_BIT_POSITION)
	{
		as_character |= (one_bit_array[i] & 1 << i);
		i++;
	}
	return (as_character);
}

/*______________________________________________________________________________
1. handles a provided character */
void	char_to_str(char character, siginfo_t *info)
{
	static char	*msg;
	static int	char_index;
	static int	msg_size;
	
	char_index = 0;
	if (msg == NULL)
		allocate_memory(&msg, &msg_size);
	if (char_index + 1 >= msg_size)
		resize_storage(&msg, &msg_size, &char_index);
	append_char(&msg, &char_index, character);
	if (character == '\0')
		print_message(&msg, &char_index, info);
}

// (3) allocates required memory on msg_storage to store a received message.
static void	allocate_memory(char **msg_storage, int *msg_size)
{
	*msg_size = 1024;
	*msg_storage = (char *)malloc(sizeof(char) * (*msg_size));
	if (*msg_storage == NULL)
	{
		ft_printf("Error: Memory allocation failed in allocate_memory.\n");
		exit(1);
	}
}


/*
______________________________________________________________________________*/
// comment
static void	resize_storage(char **msg_storage, int *msg_size, int *char_index)
{
	char	*new_msg_storage;
	int		new_msg_size;
	int		i;
	
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
		new_msg_storage[i] = (*msg_storage)[i];
		i++;
	}
	free(*msg_storage);
	*msg_storage = new_msg_storage;
	*msg_size = new_msg_size;
}
/*
______________________________________________________________________________*/
static void	append_char(char **msg, int *char_index, char character)
{
	(*msg)[(*char_index)++] = character;
}
/*
______________________________________________________________________________*/
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
______________________________________________________________________________*/

/*
______________________________________________________________________________*/
void	handle_exit(int signal)
{
	if (g_msg_storage != NULL)
	{
		free(g_msg_storage);
		g_msg_storage = NULL;
	}
	exit(0);
}

