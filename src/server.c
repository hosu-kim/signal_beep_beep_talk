/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:50:57 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/18 20:56:43 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosu-kim <hosu-kim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:49:30 by hosu-kim          #+#    #+#            */
/*   Updated: 2025/01/18 18:49:30 by hosu-kim         ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_data	g_data = {NULL, 0, 0, 0};

static void	cleanup(void)
{
	if (g_data.message)
	{
		free(g_data.message);
		g_data.message = NULL;
	}
	g_data.buffer_size = 0;
	g_data.current_bit = 0;
	g_data.current_byte = 0;
}

static int	manage_buffer(void)
{
	char	*new_buffer;
	size_t	new_size;

	if (!g_data.message)
		new_size = INITIAL_BUFFER_SIZE;
	else
	{
		if (g_data.buffer_size >= MAX_BUFFER_SIZE)
			return (0);
		new_size = g_data.buffer_size * 2;
		if (new_size > MAX_BUFFER_SIZE)
			new_size = MAX_BUFFER_SIZE;
	}
	new_buffer = (char *)malloc(new_size);
	if (!new_buffer)
		return (0);
	ft_memset(new_buffer, 0, new_size);
	if (g_data.message)
	{
		ft_memcpy(new_buffer, g_data.message, g_data.buffer_size);
		free(g_data.message);
	}
	g_data.message = new_buffer;
	g_data.buffer_size = new_size;
	return (1);
}

static void	process_byte(void)
{
	g_data.current_bit = 0;
	if (g_data.message[g_data.current_byte] == '\0')
	{
		write(1, g_data.message, g_data.current_byte);
		ft_putchar('\n');
		cleanup();
		manage_buffer();
	}
	else
		g_data.current_byte++;
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
			ft_putstr("\nBuffer full\n");
			cleanup();
			return ;
		}
	}
	if (signum == SIGUSR2)
		g_data.message[g_data.current_byte] |= (1 << g_data.current_bit);
	g_data.current_bit++;
	if (g_data.current_bit == 8)
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
		ft_putstr("Failed to initialize buffer\n");
		return (1);
	}
	ft_putstr("Server PID: ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || \
		sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		cleanup();
		ft_putstr("Signal setup failed\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
