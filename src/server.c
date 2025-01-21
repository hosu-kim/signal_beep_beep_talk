/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:25:44 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/21 21:04:38 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_data	g_data = {NULL, 0, 0, 0};

// I will clean all data in your structure for the next message.
void	cleanup(void)
{
	if (g_data.message)
		free(g_data.message);
	g_data.message = NULL;
	g_data.buffer_size = 0;
	g_data.current_bit = 0;
	g_data.current_character = 0;
}

/**
 * @brief I'll double the buffer of the message storage if necessry.
 * @details
 * -return value "1" indicates the function has terminated successfully.
 */
static int	setup_new_storage(void)
{
	char	*new_buffer;
	size_t	new_size;

	if (!g_data.message)
		new_size = INITIAL_BUFFER_SIZE;
	else
	{
		new_size = g_data.buffer_size * 2;
		if (new_size > MAX_BUFFER_SIZE)
			new_size = MAX_BUFFER_SIZE;
		if (new_size == g_data.buffer_size)
			return (0);
	}
	new_buffer = (char *)malloc(new_size);
	if (!new_buffer)
		return (0);
	ft_memset(new_buffer, 0, new_size);
	if (g_data.message)
	{
		ft_memcpy(new_buffer, g_data.message, g_data.current_character);
		free(g_data.message);
	}
	g_data.message = new_buffer;
	g_data.buffer_size = new_size;
	return (1);
}

/// @brief I'll check if seding has ended or not and print it.
/// @note g_data.message[g_data.current_character] = 0; '\0' == 0 in ascii
static void	process_byte(void)
{
	if (g_data.current_bit != 8)
		return ;
	g_data.current_bit = 0;
	if (g_data.message[g_data.current_character] == '\0')
	{
		write(1, g_data.message, g_data.current_character);
		write(1, "\n", 1);
		cleanup();
		setup_new_storage();
	}
	else
	{
		g_data.current_character++;
		if (g_data.current_character < g_data.buffer_size)
			g_data.message[g_data.current_character] = '\0';
	}
}

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (!g_data.message && !setup_new_storage())
		return ;
	if (g_data.current_character >= g_data.buffer_size - 1)
	{
		if (!setup_new_storage())
		{
			ft_putstr("\nBuffer is full. :/\n");
			return ;
		}
	}
	if (signum == SIGUSR1)
		g_data.message[g_data.current_character] |= (1 << g_data.current_bit);
	else if (signum == SIGUSR2)
		g_data.message[g_data.current_character] &= ~(1 << g_data.current_bit);
	g_data.current_bit++;
	process_byte();
}

int	main(void)
{
	if (!setup_new_storage())
	{
		cleanup();
		return (1);
	}
	write(1, "Server PID: ", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	if (!initialize_signal_handlers())
	{
		cleanup();
		return (1);
	}
	while (1)
		pause();
	return (0);
}
