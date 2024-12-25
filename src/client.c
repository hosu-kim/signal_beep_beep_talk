/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:41:03 by hoskim            #+#    #+#             */
/*   Updated: 2024/12/25 19:43:04 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	main(int argc, char *argv[])
{
	char			*pid;
	char			*msg;
	unsigned int	**msg_in_bit;
	int				i;
	int				j;

	pid = &argv[1];
	msg = &argv[2];
	if (argc != 3)
	{
		printf("Please include only two parameters: 1. Server's PID \
				2. A meassage\n");
		return (1);
	}
	i = 0;
	j = 0;
	while (*msg)
	{
		if (*msg % 2 == 1)
		{
			msg_in_bit[i][j] = msg_in_bit[i][j] * 10 + 1;
			j++;
		}
		else if (*msg % 2 == 0)
		{
			msg_in_bit[i][j] = msg_in_bit[i][j] * 10 + 0;
			j++;
		}
		i++;
	}
}
