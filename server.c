#include "minitalk.h"

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

static void	ft_pid_print(void)
{
    pid_t pid;

    pid = getpid();
    if (pid == -1)
    {
        ft_putstr_fd("Error: Cannot get PID\n", 2);
        exit(1);
    }
    ft_putstr_fd("PID -> ", 1);
    ft_putnbr_fd(pid, 1);
    ft_putchar_fd('\n', 1);
    ft_putstr_fd("Waiting for a message...\n", 1);
}

int	main(int argc, char **argv)
{
    if (argc != 1)
    {
        ft_putstr_fd("Error: This program doesn't take any arguments\n", 2);
        return (1);
    }
    (void)argv;
    ft_pid_print();
    if (signal(SIGUSR1, ft_handler) == SIG_ERR || 
        signal(SIGUSR2, ft_handler) == SIG_ERR)
    {
        ft_putstr_fd("Error: Cannot set signal handlers\n", 2);
        return (1);
    }
    while (1)
        pause();
    return (0);
}
