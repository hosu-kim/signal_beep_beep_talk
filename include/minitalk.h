/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:53:27 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/12 16:08:15 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H

# define MINITALK_H
# define _POSIX_C_SOURCE 200809L
# define MAX_BIT_POSITION 8
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include "my_printf/src/ft_printf.h"

// used in clinet.c
int		usleep(useconds_t microseconds);
// utils.h
int		ft_atoi(const char *str);
int		ft_strlen(const char *s);

#endif
