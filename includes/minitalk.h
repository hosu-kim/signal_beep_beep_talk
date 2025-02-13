/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 22:25:03 by hoskim            #+#    #+#             */
/*   Updated: 2025/02/13 22:25:03 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file minitalk.h
 * @brief Header file for the Signal beep beep talk project
 * 
 * This header contains all the necessary declarations for 
 * the Signal beep beep talk (client-server communication system).
 * It defines constants, structures, and function prototypes
 * used throughout the project.
 */
#ifndef MINITALK_H
# define MINITALK_H
# define _XOPEN_SOURCE 200        /**< Required for struct sigaction */
# define _DEFAULT_SOURCE          /**< Required for usleep() */

# include <unistd.h>              /**< For write, getpid etc. */
# include <signal.h>              /**< For sigaction struct and signal functions */
# include <stdlib.h>
# include <sys/types.h>           /**< For pid_t */

# define INITIAL_BUFFER_SIZE 1024 /**< Initial size of message buffer */
# define MAX_BUFFER_SIZE 2097152  /**< Maximum buffer size (2MB) */

/**
 * @brief Utility Functions
 */
void		ft_putstr(char *s);                                /**< Outputs string to stdout */
void		ft_putnbr(int n);                                  /**< Outputs number to stdout */
void		*ft_memset(void *s, int c, size_t n);              /**< Memory set function */
void		*ft_memcpy(void *dest, const void *src, size_t n); /**< Memory copy function */
int			ft_atoi(const char *str);                          /**< String to integer conversion */

/**
 * @brief Server Functions
 */
void		handle_exit_signal(int signum);                             /**< Handles server exit signals */
void		signal_to_char(int signum, siginfo_t *info, void *context); /**< Converts signals to chracters*/
int			initialize_signal_handlers(void);                           /**< Sets up signal handlers */
void		reset_global_data(void);                                    /**< REsets global data structure */

/**
 * @brief Data structure for message handling
 * 
 * This structure holds the state of message processing including
 * the message buffer and various position trackers.
 */
typedef struct s_data
{
	char	*message;            /**< Buffer for storing the message */
	size_t	current_buffer_size; /**< Current size of the buffer */
	size_t	bit_position;        /**< Current bit position (0-7) */
	size_t	char_index;          /**< Current chracter index in message */
}	t_data;

extern t_data	g_data;          /**< Global data structure instance */

#endif