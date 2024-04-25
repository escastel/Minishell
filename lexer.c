/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:38:48 by escastel          #+#    #+#             */
/*   Updated: 2024/04/25 16:05:44 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_tokens_util(char **line, char **tmp, int flag)
{
	char	*str;
	int		j;

	j = 0;
	str = ft_calloc(1, ft_strlen(*line));
	str[j] = **line;
	*line += 1;
	j += 1;
	if (flag)
	{
		if (**line == str[j - 1])
		{
			str[j] = **line;
			*line += 1;
			j += 1;
		}
	}
	str[j] = '\0';
	*tmp = ft_strdup(str);
	free (str);
	str = NULL;
	return (1);
}

static int	ft_tokens(char **line, char **tmp)
{
	while (**line == 32 || (**line >= 9 && **line <= 13))
		*line += 1;
	if (**line == '|')
		return (ft_tokens_util(line, tmp, 0));
	if (**line == '<')
		return (ft_tokens_util(line, tmp, 1));
	if (**line == '>')
		return (ft_tokens_util(line, tmp, 2));
	return (0);
}

static void	ft_take_first_word(char **line, char **tmp)
{
	char	*str;
	int		j ;

	if (ft_tokens(line, tmp))
		return ;
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
	return ;
}

int	lexer(t_data *data, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (ft_strlen(line) != 0)
	{
		ft_take_first_word(&line, &tmp);
		if (data->prompt[i])
			free (data->prompt[i]);
		if (ft_strcmp(tmp, "", ft_strlen(tmp)))
			data->prompt[i] = ft_strdup(tmp);
		free (tmp);
		tmp = NULL;
		i++;
	}
	return (0);
}
