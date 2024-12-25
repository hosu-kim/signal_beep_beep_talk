/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:57:09 by hoskim            #+#    #+#             */
/*   Updated: 2024/12/24 19:19:42 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

// for the ft_atoi function
int	ft_is_space(char c)
{
	return (c == '\n' || c == '\t' || c == '\r' || \
			c == '\v' || c == '\f' || c == ' ');
}

int	ft_atoi(const char *str)
{
	int	output;
	int	if_minus;

	output = 0;
	if_minus = 1;
	while (ft_is_space(*str))
		str++;
	if (*str == '-')
	{
		if_minus = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		output = output * 10 + (*str - '0');
		str++;
	}
	return (if_minus * output);
}