/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:26:26 by escastel          #+#    #+#             */
/*   Updated: 2023/05/12 13:10:02 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long int r)
{
	int	c;

	c = 0;
	while (r >= 10)
	{
		r /= 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	char		*ptr;
	int			i;
	long int	r;

	r = n;
	i = 0;
	if (n < 0)
	{
		r *= -1;
		i = 1;
	}
	i = ft_count(r) + 1 + i;
	ptr = (char *)malloc((i + 1) * sizeof(char));
	if (!ptr)
		return (0);
	ptr[i--] = '\0';
	while (i >= 0)
	{
		ptr[i] = ((r % 10) + '0');
		r /= 10;
		i--;
		if (n < 0)
			ptr[0] = '-';
	}
	return (ptr);
}
