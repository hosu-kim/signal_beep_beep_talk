/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:55:03 by hoskim            #+#    #+#             */
/*   Updated: 2025/02/13 23:10:07 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file server_utils.c
 * @brief Utility functions for the server implementation
 * 
 * This file contains utility functions specifically used by the server
 * component of the the Signal beep beep talk system
 */

#include "../includes/minitalk.h"

/**
 * @brief Handles server exit signals
 * 
 * @param signum Signal number received
 * 
 * Performs cleanup operations when the server receives an exit signal.
 */
void	handle_exit_signal(int signum)
{
	(void)signum;
	reset_global_data();
	exit(0);
}

/**
 * @brief Initializes signal handlers for the server
 * 
 * @return int Returns 1 on success, 0 on failure
 * 
 * Sets up signal handlers for SIGUSR1 and SIGUSR2, as well as exit signals
 */
int	initialize_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_to_char;
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
