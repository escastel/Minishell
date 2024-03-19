/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:40:32 by escastel          #+#    #+#             */
/*   Updated: 2024/03/16 19:42:34 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	st;

	st = start;
	if ((size_t)ft_strlen(s) <= st)
		return (ft_strdup(""));
	if ((size_t)ft_strlen(s) < (st + len))
		len = ft_strlen(s) - st;
	ptr = malloc((len + 1) * sizeof(char));
	if (!s || !ptr)
		return (0);
	ft_memcpy(ptr, s + st, len);
	ptr[len] = '\0';
	return (ptr);
}
