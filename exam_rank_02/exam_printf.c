/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exam_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 09:11:09 by agianico          #+#    #+#             */
/*   Updated: 2020/07/14 11:44:50 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int ft_putchar(char c, int n)
{
	int len = 0;
	while (n-- > 0)
	{
		write(1, &c, 1);
		len++;
	}
	return (len);
}

int ft_putstr(char *str, int n)
{
	int len = 0;
	while (n-- > 0)
	{
		write(1, &str[len], 1);
		len++;
	}
	return (len);
}

char *ft_itoa(long int num)
{
	int len = 0;
	int aux = num;
	char *str;
	while (aux /= 10)
		len++;
	if (!(str = malloc(len + 1)))
		return (0);
	str[len] = '\0';
	while (len--)
	{
		str[len] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}

char *ft_itoa_hex(unsigned int num)
{
	int len = 0;
	unsigned int aux = num;
	char *str;
	while (aux /= 16)
		len++;
	if (!(str = malloc(len + 1)))
		return (0);
	str[len] = '\0';
	while (len--)
	{
		if ((num % 16) < 10)
			str[len] = num % 16 + '0';
		if ((num % 16) > 9)
			str[len] = num % 16 + 'W';
		num /= 16;
	}
	return (str);
}

int ft_str(char *str, int width, int precision, int len)
{
	int i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
		i++;
	if (precision >= 0 && precision < i)
		i = precision;
	if (width > i)
		len += ft_putchar(' ', width - i);
	len += ft_putstr(str, i);
	return (len);
}

int ft_int(long int num, int width, int precision, int len)
{
	int i = 0;
	int neg = 0;
	if (num < 0)
	{
		num *= -1;
		neg = -1;
		width++;
	}
	char *str = ft_itoa(num);
	while (str[i])
		i++;
	if (precision == 0 && num == 0)
		width = 0;
	if (width > i)
	{
		if (precision <= i)
			width = width - i;
		else if (precision > i)
			width = width - precision;
	}
	len += ft_putchar(' ', width);
	if (negative == -1)
		len += ft_putchar('-', 1);
	len += ft_putchar('0', precision - i);
	len += ft_putstr(str, i);
	return (len);
}

int ft_printf(const char *format, ...)
{
	va_list list;
	int width = 0;
	int precision = -1;
	int len = 0;

	va_start(list, format);
	while(*format)
	{
		if (*format == '%')
		{
			format++;
			width = 0;
			precision = -1;
			while(*format >= '0' && *format <= '9')
			{
				width = width * 10 + (*format - '0'); 
				format++;
			}
			if (*format == '.')
			{
				precision = 0;
				format++;
				while(*format >= '0' && *format <= '9')
				{
					precision = precision * 10 + (*format - '0'); 
					format++;
				}
			}
			if (*format == 's')
			{
				len += ft_str(va_arg(list, char *), width, precision, len);
				format++;
			}
			if (*format == 'd')
			{
				len += ft_int((long int)va_arg(list, int), width, precision, len);
				format++;
			}
			if (*format == 'x')
			{
				len += ft_hex(va_arg(list, unsigned int), width, precision, len);
				format++;
			}
		}
		else
		{
			write(1, format, 1);
			format++;
			len++;
		}
	}
	va_end(list);
	return (len);
}
