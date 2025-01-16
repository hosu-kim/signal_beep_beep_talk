/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:34:49 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/16 17:34:49 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_handler(int signal)
{
	static int	bit;
	static char	tmp;

	if (signal == SIGUSR1)
		tmp |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_putchar_fd(tmp, 1);
		bit = 0;
		tmp = 0;
	}
}

static void ft_pid_print(pid_t pid)
{
	ft_putstr_fd("Hi, this is my PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n, 1');
	ft_putstr_fd("I'm waiting for a message...\n", 1);
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error: wrong format.\n", 1);
		ft_putstr_fd("Try: ./server\n", 1);
		return (0);
	}
	pid = getpid();
	ft_pid_print(pid);
	signal(SIGUSR1, ft_handler);
	signal(SIGUSR2, ft_handler);
	while (argc == 1)
		pause();
	return (0);
}