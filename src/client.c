/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:41:03 by hoskim            #+#    #+#             */
/*   Updated: 2024/12/24 19:12:50 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	main(int argc, char *argv[])
{
	char	*pid;
	char	*msg;

	pid = argv[1];
	msg = argv[2];
	if (argc != 3)
	{
		printf("Please include only two parameters: 1. PID 2. a meassage");
		return (1);
	}
	printf("%s", pid);
}