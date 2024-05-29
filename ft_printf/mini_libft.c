/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:23:20 by eperperi          #+#    #+#             */
/*   Updated: 2024/03/26 11:51:27 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_num(int n, int *counter)
{
	char	s;
	if (n == -2147483648)
	{
		*counter = putstr("-2147483648", counter);
		return (*counter);
	}
	if (n < 0)
	{
		*counter = print_char('-', counter);
		if (*counter == -1)
			return (-1);
		n *= -1;
	}
	else if (n == 0)
	{
		*counter = print_char('0', counter);
		return (*counter);
	}
	if (n >= 10 && *counter != -1)
		print_num (n / 10, counter);
	s = n % 10 + 48;
	*counter = print_char(s, counter);
	return (*counter);
}

int	print_unum(unsigned int n, int *counter)
{
	char	s;

	if (n == 0)
	{
		*counter += write(1, "0", 1);
		return (*counter);
	}
	if (n > 9)
		print_unum (n / 10, counter);
	s = n % 10 + 48;
	if (write(1, &s, 1) < 0)
		return (-1);
	*counter += 1;
	return (*counter);
}

int	putstr(char *s, int *counter)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		if (write(1, "(null)", 6) < 0)
		{
			*counter = -1;
			return (*counter);
		}
		*counter += 6;
		return (*counter);
	}
	while (s[i] != '\0')
	{
		if (write(1, &s[i], 1) < 0)
		{
			(*counter) = -1;
			return (*counter);
		}
		i++;
		(*counter)++;
	}
	return (*counter);
}

int	print_char(int c, int *counter)
{
	if (write(1, &c, 1) < 0)
	{
		(*counter) = -1;
		return (*counter);
	}
	(*counter)++;
	return (*counter);
}
