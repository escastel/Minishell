/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:26:02 by escastel          #+#    #+#             */
/*   Updated: 2023/09/27 16:26:54 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_piece(char *strg, int fd)
{
	char	*aux;
	int		rtn;

	if (!strg)
	{
		strg = (char *)ft_calloc_gnl(1, sizeof(char));
		if (!strg)
			return (NULL);
	}
	rtn = 1;
	aux = (char *)ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (!aux)
		return (free(strg), NULL);
	while (rtn > 0 && (!ft_strchr_gnl(aux, '\n')))
	{
		rtn = read(fd, aux, BUFFER_SIZE);
		if (rtn < 0)
			return (free(aux), free(strg), NULL);
		aux[rtn] = '\0';
		strg = ft_strjoin_gnl(strg, aux);
		if (!strg)
			return (free(strg), free(aux), NULL);
	}
	return (free(aux), strg);
}

static char	*get_line(char	*strg)
{
	char	*line;
	int		i;

	i = 0;
	if (!strg[i])
		return (NULL);
	while (strg[i] && strg[i] != '\n')
		i++;
	line = (char *)ft_calloc_gnl((i + 1 + (strg[i] == '\n')), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (strg[i] && strg[i] != '\n')
	{
		line[i] = strg[i];
		i++;
	}
	if (strg[i] && strg[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_clean(char *strg)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	while (strg[i] && strg[i] != '\n')
		i++;
	if (!strg[i])
		return (free(strg), NULL);
	new_line = (char *)ft_calloc_gnl((ft_strlen(strg) - i), sizeof(char));
	if (!new_line)
		return (free(strg), NULL);
	i++;
	j = 0;
	while (strg[i])
		new_line[j++] = strg[i++];
	new_line[j] = '\0';
	return (free(strg), new_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*strg[1000];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (free(strg[fd]), strg[fd] = NULL, NULL);
	strg[fd] = get_piece(strg[fd], fd);
	if (!strg[fd])
		return (free(strg[fd]), NULL);
	line = get_line(strg[fd]);
	if (!line)
		return (free(strg[fd]), strg[fd] = NULL, NULL);
	strg[fd] = ft_clean(strg[fd]);
	if (!strg[fd])
		return (free(strg[fd]), line);
	return (line);
}
