/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:38:09 by hoskim            #+#    #+#             */
/*   Updated: 2024/12/24 19:12:36 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	main(void)
{
	int		pid;
	char	*msg;

	pid = getpid();
	printf("Server's PID: %d\n", pid);
	while (1)
	{
		
	}

	return (0);
}

// sigaction