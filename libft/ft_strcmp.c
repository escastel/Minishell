/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:38:13 by escastel          #+#    #+#             */
/*   Updated: 2024/03/15 15:21:26 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((int)s1[i] > (int)s2[i])
			return (1);
		if ((int)s1[i] < (int)s2[i])
			return (-1);
		i++;
	}
	if (s1[i] && !s2[i])
		return (1);
	if (!s1[i] && s2[i])
		return (-1);
	return (0);
}
