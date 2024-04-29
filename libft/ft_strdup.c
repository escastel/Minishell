/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:06:46 by escastel          #+#    #+#             */
/*   Updated: 2024/04/29 12:06:27 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	size_t	i;

	cpy = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (cpy == NULL)
		return (0);
	i = 0;
	while (i <= (size_t)ft_strlen(s1))
	{
		cpy[i] = s1[i];
		i++;
	}
	return (cpy);
}
