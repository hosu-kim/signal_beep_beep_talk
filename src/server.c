/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosu-kim <hosu-kim@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:56:58 by hosu-kim         #+#    #+#             */
/*   Updated: 2025/01/17 18:56:58 by hosu-kim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#define MAX_STR 10000

static unsigned char	g_char = 0;
static int				g_bit_count = 0;
static int				g_str_index = 0;
static char				g_str[MAX_STR];

void	reset_char(void)
{
	g_char = 0;
	g_bit_count = 0;
}

void	signal_handler(int signum)
{
	g_char = g_char << 1;
	if (signum == SIGUSR2)
		g_char = g_char | 1;
	g_bit_count++;

	if (g_bit_count == 8)
	{
		g_str[g_str_index++] = g_char;
		if (g_char == '\0')
		{
			write(1, g_str, g_str_index - 1);
			write(1, "\n", 1);
			g_str_index = 0;
		}
		reset_char();
	}
}

/**
 * sigaction: a data type
 */
int	main(void)
{
	struct sigaction	sa;

	printf("Server PID: %d\n", getpid());
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(SIGUSR1, &sa, NULL) == -1 ||
		sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, "Error: sigaction failed\n", 23);
		return (1);
	}
	while (1)
		pause();
	return (0);
}
