/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:38:48 by escastel          #+#    #+#             */
/*   Updated: 2024/04/25 19:05:14 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_tokens_pipe(char **line, char **tmp)
{
	char	*str;
	int		i;

	i = 0;
	while (**line == 32 || (**line >= 9 && **line <= 13))
		*line += 1;
	str = ft_calloc(1, ft_strlen(*line));
	if (**line == '|')
	{
		str[i] = **line;
		*line += 1;
		i += 1;
		while (**line && (**line == 32 || (**line >= 9 && **line <= 13)))
			*line += 1;
		if (**line == '\0' || **line == '<')
		{
			error_msg("michishell: syntax error near unexpected token");
			free (str);
			str = NULL;
			return (1);
		}
		if (**line == '>')
		{
			*line += 1;
			while (**line && (**line == 32 || (**line >= 9 && **line <= 13)))
				*line += 1;
			if (**line == '\0')
			{
				error_msg("michishell: syntax error near unexpected token");
				free (str);
				str = NULL;
				return (1);
			}
		}
		str[i] = '\0';
		*tmp = ft_strdup(str);
		free (str);
		str = NULL;
	}
	return (0);
}

static int	ft_tokens_mayor(char **line, char **tmp)
{
	char	*str;
	int		i;

	i = 0;
	while (**line == 32 || (**line >= 9 && **line <= 13))
		*line += 1;
	str = ft_calloc(1, ft_strlen(*line));
	if (**line == '>')
	{
		str[i] = **line;
		*line += 1;
		i += 1;
		if (**line == str[i - 1]) //si <<
		{
			str[i] = **line;
			*line += 1;
			i += 1;
			while (**line && (**line == 32 || (**line >= 9 && **line <= 13)))
				*line += 1;
			if (**line == str[i - 1] || **line == '\0')  // si <<< o <<
			{
				error_msg("michishell: syntax error near unexpected token");
				free (str);
				str = NULL;
				return (1);
			}
		}
		while (**line && (**line == 32 || (**line >= 9 && **line <= 13)))
			*line += 1;
		if (**line == '<' || **line == '|' || **line == '\0') // si <> <| < o <<> <<| o << 
		{
			error_msg("michishell: syntax error near unexpected token");
			free (str);
			str = NULL;
			return (1);
		}
		str[i] = '\0';
		*tmp = ft_strdup(str);
		free (str);
		str = NULL;
	}
	return (0);
}

static int	ft_tokens_minor(char **line, char **tmp)
{
	char	*str;
	int		i;

	i = 0;
	while (**line == 32 || (**line >= 9 && **line <= 13))
		*line += 1;
	str = ft_calloc(1, ft_strlen(*line));
	if (**line == '<')
	{
		str[i] = **line;
		*line += 1;
		i += 1;
		if (**line == str[i - 1]) //si <<
		{
			str[i] = **line;
			*line += 1;
			i += 1;
			while (**line && (**line == 32 || (**line >= 9 && **line <= 13)))
				*line += 1;
			if (**line == str[i - 1] || **line == '\0')  // si <<< o <<
			{
				error_msg("michishell: syntax error near unexpected token");
				free (str);
				str = NULL;
				return (1);
			}
		}
		while (**line && (**line == 32 || (**line >= 9 && **line <= 13)))
			*line += 1;
		if (**line == '>' || **line == '|' || **line == '\0') // si <> <| < o <<> <<| o << 
		{
			error_msg("michishell: syntax error near unexpected token");
			free (str);
			str = NULL;
			return (1);
		}
		str[i] = '\0';
		*tmp = ft_strdup(str);
		free (str);
		str = NULL;
	}
	return (0);
}

static int	ft_take_first_word(char **line, char **tmp)
{
	char	*str;
	int		j ;

	if (ft_tokens_mayor(line, tmp))
		return (1);
	if (ft_tokens_minor(line, tmp))
		return (1);
	if (ft_tokens_pipe(line, tmp))
		return (1);
	j = 0;
	str = ft_calloc(1, ft_strlen(*line));
	while (**line != ' ' && **line)
	{
		j = ft_backlashes(&(*line), &str, j);
		j = ft_quotes(&(*line), &str, j);
		if (**line == '<' || **line == '>' || **line == '|')
			break ;
		if (**line != ' ')
		{
			str[j] = **line;
			*line += 1;
			j += 1;
		}
	}
	str[j] = '\0';
	*tmp = ft_strdup(str);
	free (str);
	return (0);
}

int	lexer(t_data *data, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (ft_strlen(line) != 0)
	{
		if (ft_take_first_word(&line, &tmp) == 1)
			return (1);
		if (tmp && ft_strncmp(tmp, "", ft_strlen(tmp)))
			data->prompt[i] = ft_strdup(tmp);
		printf("%s\n", data->prompt[i]);
		free (tmp);
		tmp = NULL;
		i++;
	}
	return (0);
}
