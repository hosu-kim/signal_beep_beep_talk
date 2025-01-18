/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 00:57:31 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/18 00:57:31 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define _XOPEN_SOURCE 700 // 불완전한 형식 "struct sigaction"은(는) 허용되지 않음

# include <unistd.h> // write, getpid 등
# include <signal.h> // sigaction 구조체, signal 관련 함수들
# include <stdlib.h>
# include <sys/types.h> // pid_t

# define BUFFER_SIZE 10000

typedef struct s_data
{
	char	message[BUFFER_SIZE];
	int		current_bit;
	int		current_byte;
}	t_data;

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int n);
#endif