/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:02:54 by escastel          #+#    #+#             */
/*   Updated: 2023/09/27 16:31:29 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthexa(unsigned long long nb, char c)
{
	int	count;

	count = 0;
	if (nb >= 16)
		count += ft_puthexa(nb / 16, c);
	if (c == 'X')
		ft_putchar("0123456789ABCDEF"[nb % 16]);
	if (c == 'x')
		ft_putchar("0123456789abcdef"[nb % 16]);
	count++;
	return (count);
}
