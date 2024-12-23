/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:38:09 by hoskim            #+#    #+#             */
/*   Updated: 2024/12/23 22:05:14 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	handler(int sig)
{
	printf("Recieved a signal. Terminating the program. \
	Signal number: %d\n", sig);
	sleep(2);
	exit(0);
}

int	main(void)
{
	signal(SIGINT, handler);
	printf("Type \"ctrl+c\"\n");
	while (1);
	return (0);
}