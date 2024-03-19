/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:26:08 by escastel          #+#    #+#             */
/*   Updated: 2023/09/27 16:26:22 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *s)
{
	int	c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}

int	ft_strchr_gnl(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return (1);
		s++;
	}
	return (0);
}

void	*ft_calloc_gnl(size_t count, size_t size)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)malloc((count * size));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	ptr = (char *)ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 1, sizeof(char));
	if (!ptr)
		return (free(s1), NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	return (free(s1), ptr);
}
