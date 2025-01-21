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
# define _XOPEN_SOURCE 200 // 불완전한 형식 "struct sigaction"은(는) 허용되지 않음
# define _DEFAULT_SOURCE // ulseep()

# include <unistd.h> // write, getpid 등
# include <signal.h> // sigaction 구조체, signal 관련 함수들
# include <stdlib.h>
# include <sys/types.h> // pid_t

# define INITIAL_BUFFER_SIZE 1024
# define MAX_BUFFER_SIZE 2097152 // 2MB

typedef struct s_data
{
	char	*message;
	size_t	buffer_size;
	size_t	current_bit;
	size_t	current_character;
}	t_data;

// 전역 변수 선언
extern t_data	g_data;

// 필수 함수 선언
void	ft_putstr(char *s);
void	ft_putnbr(int n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_atoi(const char *str);

#endif