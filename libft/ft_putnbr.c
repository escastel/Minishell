/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:05:03 by escastel          #+#    #+#             */
/*   Updated: 2023/09/27 16:31:21 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int nb)
{
	int	count;

	count = ft_count_nb(nb);
	if (nb == -2147483648)
	{
		write(1, "-2", 2);
		nb = 147483648;
		count += ft_count_nb(nb);
	}
	else if (nb < 0)
	{
		write (1, "-", 1);
		nb *= -1;
	}
	if (nb >= 0 && nb <= 9)
	{
		nb += '0';
		write(1, &nb, 1);
	}
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	return (count);
}
