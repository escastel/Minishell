/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:03:21 by escastel          #+#    #+#             */
/*   Updated: 2023/09/27 16:31:16 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(unsigned long long ptr)
{
	int	count;

	count = 0;
	count += ft_putstr("0x");
	count += ft_puthexa(ptr, 'x');
	return (count);
}
