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

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

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