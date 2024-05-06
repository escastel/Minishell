/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:04:43 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/05/06 12:35:38 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*ft_get_str(int fd, char *str)
{
	int		redret;
	char	*aux;

	if (!str)
		str = ft_challoc(1);
	aux = ft_challoc(BUFFER_SIZE + 1);
	redret = 42;
	while (!ft_srchnl(aux) && redret > 0)
	{
		redret = read(fd, aux, BUFFER_SIZE);
		if (redret < 0)
			return (free(aux), free(str), NULL);
		aux[redret] = 0;
		str = gnl_ft_strjoin(str, aux);
		if (!str)
			return (free(aux), free(str), NULL);
	}
	free(aux);
	return (str);
}

static char	*ft_get_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i += 1;
	line = ft_challoc(i + 1 + (str[i] == '\n'));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i += 1;
	}
	if (str[i])
		line[i++] = '\n';
	line[i] = 0;
	return (line);
}

static char	*ft_liberator(char *str)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i += 1;
	if (str[i] == 0)
		return (free(str), NULL);
	aux = ft_challoc(gnl_ft_strlen(str) - i);
	i += 1;
	j = 0;
	while (str[i + j])
	{
		aux[j] = str[i + j];
		j += 1;
	}
	aux[j] = 0;
	free(str);
	return (aux);
}

char	*get_next_line2(int fd)
{
	char		*line;
	static char	*str[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (str[fd])
		{
			free(str[fd]);
			str[fd] = NULL;
		}
		return (NULL);
	}
	str[fd] = ft_get_str(fd, str[fd]);
	if (str[fd] == NULL)
		return (NULL);
	line = ft_get_line(str[fd]);
	str[fd] = ft_liberator(str[fd]);
	return (line);
}

char	*ft_challoc(size_t count)
{
	char		*ret;
	size_t		i;

	ret = malloc(count);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		ret[i] = 0;
		i += 1;
	}
	return (ret);
}
