/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_unsignb.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:53:01 by escastel          #+#    #+#             */
/*   Updated: 2023/09/27 16:35:34 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_unsignb(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb <= -1)
		count += 1;
	while (nb >= 10)
	{
		nb /= 10;
		count++;
	}
	return (count);
}
