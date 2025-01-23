/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:25:44 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/23 19:00:05 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_data	g_data = {NULL, 0, 0, 0};

// initialize all members to NULL and 0 in g_data.
void	reset_global_data(void)
{
	if (g_data.message)
		free(g_data.message);
	g_data.message = NULL;
	g_data.current_buffer_size = 0;
	g_data.bit_position = 0;
	g_data.char_index = 0;
}

/**
 * @brief It sets a sufficient buffer size to save the message.
 * @details return value 1 indicates the function has terminated successfully.
 */
static int	resize_message_buffer(void)
{
	char	*buffer_for_update;
	size_t	buffer_size_to_set;

	if (g_data.message == NULL)
		buffer_size_to_set = INITIAL_BUFFER_SIZE;
	else
	{
		buffer_size_to_set = g_data.current_buffer_size * 2;
		if (buffer_size_to_set > MAX_BUFFER_SIZE)
			buffer_size_to_set = MAX_BUFFER_SIZE;
		if (buffer_size_to_set == g_data.current_buffer_size)
			return (0);
	}
	buffer_for_update = (char *)malloc(buffer_size_to_set);
	if (!buffer_for_update)
		return (0);
	ft_memset(buffer_for_update, 0, buffer_size_to_set);
	if (g_data.message)
	{
		ft_memcpy(buffer_for_update, g_data.message, g_data.char_index);
		free(g_data.message);
	}
	g_data.message = buffer_for_update;
	g_data.current_buffer_size = buffer_size_to_set;
	return (1);
}

/** @brief If Null character is detected, it prints the completed string,
 *	       or if more data remains, continues to build the completed string.
 
 *  @note g_data.message[g_data.current_character] = 0; '\0' == 0 in ascii
 */		
static void	process_completed_str(void)
{
	if (g_data.bit_position != 8)
		return ;
	g_data.bit_position = 0;
	if (g_data.message[g_data.char_index] == '\0')
	{
		write(1, g_data.message, g_data.char_index);
		write(1, "\n", 1);
		reset_global_data();
		resize_message_buffer();
	}
	else
	{
		g_data.char_index++;
		if (g_data.char_index >= g_data.current_buffer_size)
		{
			if (!resize_message_buffer())
				exit(EXIT_FAILURE);
		}
		if (g_data.char_index < g_data.current_buffer_size)
			g_data.message[g_data.char_index] = '\0';
	}
}

/**
 * @brief  it converts signals to char and stores the message buffer
 */
void	signal_to_char(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (!g_data.message && !resize_message_buffer())
		return ;
	if (g_data.char_index >= g_data.current_buffer_size - 1)
	{
		if (!resize_message_buffer())
		{
			ft_putstr("\nBuffer is full... :/\n");
			return ;
		}
	}
	if (signum == SIGUSR1)
		g_data.message[g_data.char_index] |= (1 << g_data.bit_position);
	else if (signum == SIGUSR2)
		g_data.message[g_data.char_index] &= ~(1 << g_data.bit_position);
	g_data.bit_position++;
	process_completed_str();
}

int	main(void)
{
	if (!resize_message_buffer())
	{
		reset_global_data();
		return (1);
	}
	write(1, "Server PID: ", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	if (!initialize_signal_handlers())
	{
		reset_global_data();
		return (1);
	}
	while (1)
		pause();
	return (0);
}
