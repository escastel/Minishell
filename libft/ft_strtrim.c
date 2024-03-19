/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:38:53 by escastel          #+#    #+#             */
/*   Updated: 2023/05/03 15:22:27 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s;
	size_t	e;

	e = ft_strlen(s1);
	s = 0;
	if (*s1 == '\0' && e == 0)
		return (ft_strdup(""));
	if (!s1 || !set)
		return (0);
	while (ft_strchr(set, s1[s]))
		s++;
	while (ft_strrchr(set, s1[e]))
		e--;
	return (ft_substr(s1, s, e - s + 1));
}
