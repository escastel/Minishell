/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:21:01 by escastel          #+#    #+#             */
/*   Updated: 2023/05/12 13:10:35 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*o;
	unsigned char	*t;

	i = 0;
	o = (unsigned char *)s1;
	t = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if ((size_t)o[i] > (size_t)t[i])
			return ((size_t)o[i] - (size_t)t[i]);
		if ((size_t)o[i] < (size_t)t[i])
			return ((size_t)o[i] - (size_t)t[i]);
		i++;
	}
	return (0);
}
