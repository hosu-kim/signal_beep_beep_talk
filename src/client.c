/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:43:08 by hoskim            #+#    #+#             */
/*   Updated: 2025/02/13 22:55:45 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file client.c
 * @brief Client implementation for the Signal beep beep talk project
 * 
 * This file contains the implementation of the client side of the communication
 * system. It sends message to the server by converting
 * characters to binary signals.
 */
#include "../includes/minitalk.h"

/**
 * @brief Sends a single character as a sequence of bits to the server
 * 
 * @param server_pid PID of the server process
 * @param character The character to be sent
 * @param bit_position Current bit position (0-7)
 * 
 * This function recursively sends each bit of a character to the server
 * using SIGUSR1 for 1 and SIGUSR2 for 0.
 */
void	send_char_as_bits(pid_t server_pid, char character, int bit_position)
{
	if (bit_position < 8)
	{
		if ((character >> bit_position) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(700);
		send_char_as_bits(server_pid, character, bit_position + 1);
	}
}

/**
 * @brief Iterates through a string and sends each character to the server
 * 
 * @param server_pid PID of the server process
 * @param str The string to be sent
 * 
 * This function sends each character of the string followed 
 * by a null terminaotor
 */
void	iterate_string(pid_t server_pid, char *str)
{
	if (*str)
	{
		send_char_as_bits(server_pid, *str, 0);
		iterate_string(server_pid, str + 1);
	}
	else
		send_char_as_bits(server_pid, '\0', 0);
}

/**
 * @brief Main function for the client program
 * 
 * @param argc Argument count
 * @param argv Argument vector
 * @return int Returns 0 on success, 1 on error
 * 
 * Validates input arguments and initiates the message sending process.
 */
int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
	{
		ft_putstr("Usage: ./client [server_pid] [message]\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_putstr("Error: Invalid server PID\n");
		return (1);
	}
	iterate_string(server_pid, argv[2]);
	return (0);
}
