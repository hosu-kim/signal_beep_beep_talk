/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:25:44 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/20 22:16:48 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_data	g_data = {NULL, 0, 0, 0};

// I will clean all data in your structure for the next message.
static void	cleanup(void)
{
	if (g_data.message)
		free(g_data.message);
	g_data.message = NULL;
	g_data.buffer_size = 0;
	g_data.current_bit = 0;
	g_data.current_byte = 0;
}

/**
 * @brief I will double the buffer of the message storage if necessry.
 * @details
 * -return value "1" indicates the function has terminated successfully.
 */
static int	manage_buffer(void)
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
		ft_memcpy(new_buffer, g_data.message, g_data.current_byte);
		free(g_data.message);
	}
	g_data.message = new_buffer;
	g_data.buffer_size = new_size;
	return (1);
}

/// @brief I will check if seding a message has done or not and print it.
/// @param  
static void	process_byte(void)
{
	if (g_data.current_bit != 8)
		return ;
	g_data.current_bit = 0;
	if (g_data.message[g_data.current_byte] == '\0')
	{
		write(1, g_data.message, g_data.current_byte);
		write(1, "\n", 1);
		cleanup();
		manage_buffer();
	}
	else
	{
		g_data.current_byte++;
		if (g_data.current_byte < g_data.buffer_size)
			g_data.message[g_data.current_byte] = 0;
	}
}

static void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (!g_data.message && !manage_buffer())
		return ;
	if (g_data.current_byte >= g_data.buffer_size - 1)
	{
		if (!manage_buffer())
		{
			ft_putstr("\nBuffer is full.\n");
			return ;
		}
	}
	if (signum == SIGUSR1)
		g_data.message[g_data.current_byte] |= (1 << g_data.current_bit);
	else if (signum == SIGUSR2)
		g_data.message[g_data.current_byte] &= ~(1 << g_data.current_bit);
	g_data.current_bit++;
	process_byte();
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (!manage_buffer())
	{
		ft_putstr("Failed to initialize buffer.\n");
		return (1);
	}
	write(1, "Server PID: ", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || \
		sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		cleanup();
		ft_putstr("Signal setup failed.\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
