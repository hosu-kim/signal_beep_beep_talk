#include "../include/minitalk.h"

#define INITIAL_SIZE 10000
#define GROWTH_FACTOR 2

static unsigned char	g_char = 0;
static int			g_bit_count = 0;
static int			g_str_index = 0;
static int			g_str_capacity = INITIAL_SIZE;
static char			*g_str = NULL;

void	reset_char(void)
{
    g_char = 0;
    g_bit_count = 0;
}

int	grow_buffer(void)
{
    char	*new_str;
    int		new_capacity;
    int		i;

    new_capacity = g_str_capacity * GROWTH_FACTOR;
    new_str = (char *)malloc(new_capacity);
    if (!new_str)
        return (0);
    if (g_str)
    {
        i = 0;
        while (i < g_str_index)
        {
            new_str[i] = g_str[i];
            i++;
        }
        free(g_str);
    }
    g_str = new_str;
    g_str_capacity = new_capacity;
    return (1);
}

void	signal_handler(int signum)
{
    g_char = g_char << 1;
    if (signum == SIGUSR2)
        g_char = g_char | 1;
    g_bit_count++;

    if (g_bit_count == 8)
    {
        if (g_str_index >= g_str_capacity - 1)
        {
            if (!grow_buffer())
            {
                write(2, "Error: Memory allocation failed\n", 31);
                return ;
            }
        }
        g_str[g_str_index++] = g_char;
        if (g_char == '\0')
        {
            write(1, g_str, g_str_index - 1);
            write(1, "\n", 1);
            g_str_index = 0;
        }
        reset_char();
    }
}

int	main(void)
{
    struct sigaction	sa;

    g_str = (char *)malloc(INITIAL_SIZE);
    if (!g_str)
    {
        write(2, "Error: Initial memory allocation failed\n", 38);
        return (1);
    }

    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    printf("Server PID: %d\n", getpid());

    if (sigaction(SIGUSR1, &sa, NULL) == -1 ||
        sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        write(2, "Error: sigaction failed\n", 23);
        free(g_str);
        return (1);
    }
    while (1)
        pause();
    free(g_str);
    return (0);
}
