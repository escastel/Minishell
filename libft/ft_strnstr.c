/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:13:36 by escastel          #+#    #+#             */
/*   Updated: 2023/05/12 13:12:52 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < n)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while ((haystack[i + j] == needle[j]) && (i + j) < n)
			{
				j++;
				if (needle[j] == '\0')
					return (&((char *)haystack)[i]);
			}
		}
		i++;
	}
	return (0);
}
