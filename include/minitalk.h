/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:53:27 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/08 19:55:58 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H

# define MINITALK_H
# define _POSIX_C_SOURCE 200809L
# define BUFFER_SIZE 8
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "my_printf/src/ft_printf.h"

// utils.h
int	ft_atoi(const char *str);
int	ft_strlen(const char *s);

void	signal_proccessor(int signal, siginfo_t *info, void *context);

#endif
