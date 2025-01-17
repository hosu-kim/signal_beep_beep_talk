/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:29:25 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/17 21:29:25 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosu-kim <hosu-kim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:28:44 by hosu-kim          #+#    #+#             */
/*   Updated: 2025/01/17 20:28:44 by hosu-kim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	ft_putnbr(int n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

static void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static int		bit = 0;
	static int		i = 0;
	static char		str[10000];

	(void)context;
	if (signum == SIGUSR1)
		str[i] |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		if (str[i] == '\0')
		{
			ft_putstr(str);
			ft_putchar('\n');
			i = 0;
			bit = 0;
			ft_memset(str, 0, sizeof(str));
		}
		else
		{
			bit = 0;
			i++;
		}
	}
	if (kill(info->si_pid, SIGUSR2) == -1)
	{
		ft_putstr("Error: Failed to send acknowledgment signal\n");
		exit(1);
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr("Server PID: ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || \
		sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr("Error: Failed to set up signal handlers\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}