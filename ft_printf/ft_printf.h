/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:55:11 by eperperi          #+#    #+#             */
/*   Updated: 2024/05/29 12:37:31 by eperperi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <string.h>
# include <stdarg.h>
# include <limits.h>

int		print_char(int c, int *counter);
int		print_unum(unsigned int n, int *counter);
int		print_num(int n, int *counter);
int		putstr(char *s, int *counter);
void	print_hex(char *res, int hex_len, int *counter);
char	*hex_calc(unsigned int n, int *counter, char c);
int		print_cases(const char *input, va_list args, int i, int *counter);
int		ft_printf(const char *input, ...);
int		p_calc(unsigned long n, int *counter);
int		check_null_p(unsigned long n);
int		check_null_hex(unsigned long n, int *counter);
void	print_p(char *res, int hex_len, int *counter);

#endif