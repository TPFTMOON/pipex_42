/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:10:41 by abaryshe          #+#    #+#             */
/*   Updated: 2025/01/09 09:24:33 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_format(const char *format, va_list args)
{
	int	len;

	len = 0;
	if (*format == '%')
		len = ft_print_char('%');
	else if (*format == 's')
		len = ft_print_str(va_arg(args, char *));
	else if (*format == 'c')
		len = ft_print_char(va_arg(args, int));
	else if (*format == 'p')
		len = ft_print_ptr(va_arg(args, void *));
	else if (*format == 'd' || *format == 'i')
		len = ft_print_num(va_arg(args, int));
	else if (*format == 'u')
		len = ft_print_u(va_arg(args, unsigned int));
	else if (*format == 'x' || *format == 'X')
		len = ft_print_hex(va_arg(args, unsigned int), *format);
	else
	{
		len = ft_print_char('%');
		len = ft_print_char(*format);
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	if (!format)
		return (-1);
	va_start(args, format);
	len = 0;
	while (*format)
	{
		if (*format == '%')
			len += ft_print_format(++format, args);
		else
			len += ft_print_char(*format);
		format++;
	}
	va_end(args);
	return (len);
}
/*
#include <stdio.h>

int	main(void)
{
	int				len1;
	int				len2;
	char			ch;
	char			*str;
	int				a;
	unsigned int	u;
	unsigned int	x;
	char			*n;

	len1 = 0;
	len2 = 0;
	ch = 'q';
	str = "WE DID IT";
	a = -2147483648; //-2147483648
	u = 4294967295;
	x = 3740932484; // 4294967295 // 3740932484
	n = NULL;
	ft_printf("character:\n");
	len1 += ft_printf("%c\n", ch);
	ft_printf("-----------------------------------------------\n");
	len2 += printf("%c\n", ch);
	ft_printf("Total printed:\n");
	printf("ft_printf: %d\n", len1);
	ft_printf("-----------------------------------------------\n");
	printf("printf: %d\n", len2);
	ft_printf("\n");
	ft_printf("string:\n");
	len1 += ft_printf("%s\n", str);
	ft_printf("-----------------------------------------------\n");
	len2 += printf("%s\n", str);
	ft_printf("Total printed:\n");
	printf("ft_printf: %d\n", len1);
	ft_printf("-----------------------------------------------\n");
	printf("printf: %d\n", len2);
	ft_printf("\n");
	ft_printf("string adress: \n");
	len1 += ft_printf("%p\n", &str);
	ft_printf("-----------------------------------------------\n");
	len2 += printf("%p\n", &str);
	ft_printf("Total printed:\n");
	printf("ft_printf: %d\n", len1);
	ft_printf("-----------------------------------------------\n");
	printf("printf: %d\n", len2);
	ft_printf("\n");
	ft_printf("int:\n");
	len1 += ft_printf("%d\n", a);
	ft_printf("-----------------------------------------------\n");
	len2 += printf("%d\n", a);
	ft_printf("Total printed:\n");
	printf("ft_printf: %d\n", len1);
	ft_printf("-----------------------------------------------\n");
	printf("printf: %d\n", len2);
	ft_printf("\n");
	ft_printf("int with %%i:\n");
	len1 += ft_printf("%i\n", a);
	ft_printf("-----------------------------------------------\n");
	len2 += printf("%i\n", a);
	ft_printf("Total printed:\n");
	printf("ft_printf: %d\n", len1);
	ft_printf("-----------------------------------------------\n");
	printf("printf: %d\n", len2);
	ft_printf("\n");
	ft_printf("unsigned int:\n");
	len1 += ft_printf("%u\n", u);
	ft_printf("-----------------------------------------------\n");
	len2 += printf("%u\n", u);
	ft_printf("Total printed:\n");
	printf("ft_printf: %d\n", len1);
	ft_printf("-----------------------------------------------\n");
	printf("printf: %d\n", len2);
	ft_printf("\n");
	ft_printf("hex int lower:\n");
	len1 += ft_printf("%x\n", x);
	ft_printf("-----------------------------------------------\n");
	len2 += printf("%x\n", x);
	ft_printf("Total printed:\n");
	printf("ft_printf: %d\n", len1);
	ft_printf("-----------------------------------------------\n");
	printf("printf: %d\n", len2);
	ft_printf("\n");
	ft_printf("hex int UPPER:\n");
	len1 += ft_printf("%X\n", x);
	ft_printf("-----------------------------------------------\n");
	len2 += printf("%X\n", x);
	ft_printf("Total printed:\n");
	printf("ft_printf: %d\n", len1);
	ft_printf("-----------------------------------------------\n");
	printf("printf: %d\n", len2);
	ft_printf("\n");
	ft_printf("NULL as string:\n");
	len1 += ft_printf("%s\n", n);
	ft_printf("-----------------------------------------------\n");
	len2 += printf("%s\n", n);
	ft_printf("Total printed:\n");
	printf("ft_printf: %d\n", len1);
	ft_printf("-----------------------------------------------\n");
	printf("printf: %d\n", len2);
	ft_printf("\n");
	ft_printf("NULL as pointer:\n");
	len1 += ft_printf("%p\n", n);
	ft_printf("-----------------------------------------------\n");
	len2 += printf("%p\n", n);
	ft_printf("\n");
	ft_printf("Total printed:\n");
	printf("ft_printf: %d\n", len1);
	ft_printf("-----------------------------------------------\n");
	printf("printf: %d\n", len2);
	printf("\n");
	printf("%d\n", ft_printf(0));
	printf("%d\n", printf(0));
	ft_printf("wow: %H");
	printf("wow: %H");
	return (0);
}*/
