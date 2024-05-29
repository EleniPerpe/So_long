/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_p_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:33:44 by eperperi          #+#    #+#             */
/*   Updated: 2024/03/26 12:42:46 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// void print_p(char *res, int hex_len);
// int	check_null_p(unsigned long n);

int	p_calc(unsigned long n, int *counter)
{
	char	*res;
	int		hex_len;
	int		temp;

	hex_len = check_null_p(n);
	temp = hex_len;
	res = malloc((hex_len + 3) * sizeof(char));
	if (!res)
	{
		*counter = -1;
		return (free(res), *counter);
	}
	(*counter) += 2;
	while (--hex_len >= 0)
	{
		if (n % 16 > 9)
			res[hex_len + 2] = ((n % 16) + 87);
		else
			res[hex_len + 2] = ((n % 16) + 48);
		(*counter)++;
		n = n / 16;
	}
	print_p(res, temp, counter);
	return (free(res), *counter);
}

void print_p(char *res, int hex_len, int *counter)
{
	res[0] = '0';
	res[1] = 'x';
	res[hex_len + 2] = '\0';
	while (*res)
	{
		if (write(1, res, 1) < 0)
		{
			*counter = -1;
			return ;
		}
		res++;
		(*counter)++;
	}
	return ;
}

int	check_null_p(unsigned long n)
{
	int	hex_len;

	hex_len = 0;
	if (n == 0)
		hex_len = 1;
	else
	{
		while (n > 0)
		{
			n /= 16;
			hex_len++;
		}
	}
	return (hex_len);
}
