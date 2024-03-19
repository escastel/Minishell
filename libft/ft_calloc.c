/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:18:20 by escastel          #+#    #+#             */
/*   Updated: 2023/05/12 13:09:45 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)malloc(count * size);
	if (!ptr)
		return (0);
	i = 0;
	while (i < (count * size))
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}
