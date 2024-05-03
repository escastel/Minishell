/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:53:17 by escastel          #+#    #+#             */
/*   Updated: 2024/05/03 17:58:42 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	token_utils(char **line, char **tmp, int *i)
{
	char	*str;

	str = ft_calloc(1, ft_strlen(*line) + 1);
	str[*i] = **line;
	*line += 1;
	*i += 1;
	if (**line == str[*i - 1])
	{
		str[*i] = **line;
		*line += 1;
		*i += 1;
		while (**line && (**line == 32 || (**line >= 9 && **line <= 13)))
			*line += 1;
		if (**line == str[*i - 1] || **line == '\0')
		{
			error_msg("michishell: syntax error near unexpected token");
			return (258);
		}
	}
	while (**line && (**line == 32 || (**line >= 9 && **line <= 13)))
		*line += 1;
	str[*i] = '\0';
	*tmp = ft_strdup(str);
	free (str);
	return (0);
}

int	ft_tokens_mayor(char **line, char **tmp)
{
	int		i;

	i = 0;
	if (**line == '>')
	{
		if (token_utils(line, tmp, &i))
			return (258);
		if (**line == '<' || **line == '|' || **line == '\0')
		{
			error_msg("michishell: syntax error near unexpected token");
			return (258);
		}
		return (2);
	}
	return (0);
}

int	ft_tokens_minor(char **line, char **tmp)
{
	int		i;

	i = 0;
	if (**line == '<')
	{
		if (token_utils(line, tmp, &i))
			return (1);
		if (**line == '>' || **line == '|' || **line == '\0')
		{
			error_msg("michishell: syntax error near unexpected token");
			return (258);
		}
		return (2);
	}
	return (0);
}

int	ft_tokens_pipe(char **line, char **tmp)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_calloc(1, ft_strlen(*line) + 1);
	printf("%p\n", str);
	if (**line == '|')
	{
		str[i] = **line;
		*line += 1;
		while (**line && (**line == 32 || (**line >= 9 && **line <= 13)))
			*line += 1;
		if (**line == '\0')
		{
			error_msg("michishell: syntax error near unexpected token");
			return (258);
		}
		str[++i] = '\0';
		*tmp = ft_strdup(str);
		free (str);
		return (2);
	}
	return (0);
}
