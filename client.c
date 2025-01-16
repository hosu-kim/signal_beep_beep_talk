/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:58:31 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/16 17:08:31 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_send_bit(pid_t pid, char input)
{
	int	bit;

	bit = 0;
	while (bit < 8)

	{
		if ((input & (1 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

static void	ft_send_str(pid_t pid, char input[])
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		ft_send_bit(pid, input[i]);
		i++;
	}
	ft_send_bit(pid, '\n');
	ft_send_bit(pid, '\0');
}