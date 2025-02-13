/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosu-kim <hosu-kim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:42:30 by hosu-kim          #+#    #+#            */
/*   Updated: 2025/01/18 18:42:30 by hosu-kim         ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils.c
 * @brief Utility functions implementation
 * 
 * This file contains the implementation of various utility functions used
 * throughout the Signal beep beep talk project, including string output,
 * number conversion, and memory manipulation functions.
 */

#include "../includes/minitalk.h"

/**
 * @brief Outputs a string to standard output
 * 
 * @param string String to be written
 * 
 * Writes the input string to standard output character by character.
 * Returns without action if the input string is NULL.
 */
void	ft_putstr(char *string)
{
	int	i;

	if (!string)
		return ;
	i = 0;
	while (string[i])
		write(1, &string[i++], 1);
}

/**
 * @brief Outputs an integer to standard output
 * 
 * @param number Integer number to be written
 * 
 * Converts the integer to its string representation and outputs it.
 * Handles negative numbers and INT_MIN specially.
 */
void	ft_putnbr(int number)
{
	char	c;

	if (number == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (number < 0)
	{
		write(1, "-", 1);
		number = -number;
	}
	if (number >= 10)
		ft_putnbr(number / 10);
	c = (number % 10) + '0';
	write(1, &c, 1);
}

/**
 * @brief fills a block of memory with a specified value
 * 
 * @param s Pointer to memory area to be filled
 * @param c Value to be set (converted to unsigned char)
 * @param n Number of bytes to be set
 * @return Pointer to the memory area s
 * 
 * Sets n bytes of memory starting at s to the value c.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
		ptr[i++] = (unsigned char)c;
	return (s);
}

/**
 * brief Copies memory area
 * 
 * @param dest Pointer to destination memory area
 * @param src Pointer to source memory area
 * @param n Numver of bytes to copy
 * @return Pointer to destination
 * 
 * Copies n bytes from memory area src to memory area dest.
 * Return NULL if both src and dest are NULL.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/**
 * @brief Converts a string to an integer
 * 
 * @param str String to be converted
 * @return Converted integer value
 * 
 * Skips whitespace, handles optional sign, and converts
 * numeric characters to integer value. Return 0 if no
 * vaild conversion could be performed.
 */
int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == '\n' || *str == '\t' || *str == '\r' || \
			*str == '\v' || *str == '\f' || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}
