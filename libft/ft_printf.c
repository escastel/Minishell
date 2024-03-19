/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:16:16 by escastel          #+#    #+#             */
/*   Updated: 2023/09/27 16:31:37 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_filter(char const *str, int i, va_list	*args)
{
	int	count;

	count = 0;
	if (str[i] == 'c')
		count += ft_putchar(va_arg(*args, int));
	if (str[i] == 's')
		count += ft_putstr(va_arg(*args, char *));
	if (str[i] == 'p')
		count += ft_putptr(va_arg(*args, unsigned long long));
	if (str[i] == 'd')
		count += ft_putnbr(va_arg(*args, int));
	if (str[i] == 'i')
		count += ft_putnbr(va_arg(*args, int));
	if (str[i] == 'u')
		count += ft_putunsignbr(va_arg(*args, unsigned int));
	if (str[i] == 'x')
		count += ft_puthexa(va_arg(*args, unsigned int), 'x');
	if (str[i] == 'X')
		count += ft_puthexa(va_arg(*args, unsigned int), 'X');
	if (str[i] == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			count += ft_filter(str, i, &args);
		}
		else
			count += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
