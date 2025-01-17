<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:53:27 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/17 18:00:04 by hoskim           ###   ########.fr       */
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

=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:30:43 by hoskim            #+#    #+#             */
/*   Updated: 2025/01/17 21:30:43 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>  // for memset

void	ft_putnbr(int n);
void	ft_putstr(char *str);
void	ft_putchar(char c);

>>>>>>> b32b9bf70c8fbbbc5b3539b8a933832f15df2b58
#endif