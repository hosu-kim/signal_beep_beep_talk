/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:27:59 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/16 17:27:59 by hoskim           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc == 3 && argv[2][0] != '\0')
	{
		pid = ft_atoi(argv[1]);
		if (pid < 100 || pid > 99999)
		{
			ft_putstr_fd("Error: wrong pid.\n", 1);
			return (0);
		}
		ft_send_str(pid, argv[2]);
	}
	else{
		ft_putstr_fd("Error: wrong format.\n", 1);
		ft_putstr_fd("Try: ./clien [PID] [MESSAGE]\n", 1);
	}
	return (0);
}
