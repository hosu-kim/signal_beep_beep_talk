/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:55:03 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/21 21:03:33 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	handle_exit_signal(int signum)
{
	(void)signum;
	cleanup();
	exit(0);
}

int	initialize_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (0);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (0);
	signal(SIGINT, handle_exit_signal);
	signal(SIGTERM, handle_exit_signal);
	return (1);
}
