/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:38:48 by escastel          #+#    #+#             */
/*   Updated: 2024/05/02 18:26:19 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static int	tokens(char **line, char **tmp)
{
	int	flag;

	while (**line == 32 || (**line >= 9 && **line <= 13))
		*line += 1;
	flag = ft_tokens_mayor(line, tmp);
	if (flag)
		return (flag);
	flag = ft_tokens_minor(line, tmp);
	if (flag)
		return (flag);
	flag = ft_tokens_pipe(line, tmp);
	if (flag)
		return (flag);
	return (0);
}

static int	ft_take_first_word(char **line, char **tmp)
{
	char	*str;
	int		flag;
	int		j;

	flag = tokens(line, tmp);
	if (flag)
		return (flag);
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
			str[j++] = **line;
			*line += 1;
		}
	}
	while (**line == 32 || (**line >= 9 && **line <= 13))
		*line += 1;
	str[j] = '\0';
	*tmp = ft_strdup(str);
	free (str);
	return (0);
}

int	lexer(t_data *data, char *line)
{
	char	*tmp;
	char	**prompt;
	int		i;

	i = 0;
	tmp = NULL;
	prompt = ft_calloc(ft_strlen(line) + 1, sizeof(char *));
	while (*line)
	{
		if (ft_take_first_word(&line, &tmp) == 258)
		{
			if (tmp)
				free (tmp);
			i = -1;
			if (prompt[++i])
			{
				i = -1;
				while (prompt[++i])
					free (prompt[i]);
				free (prompt);
			}
			data->status = 258;
			return (1);
		}
		if (tmp && ft_strncmp(tmp, "", ft_strlen(tmp)))
			prompt[i] = ft_strdup(tmp);
		else
		{
			i = -1;
			if (prompt[++i])
			{
				i = -1;
				while (prompt[++i])
					free (prompt[i]);
				free (prompt);
			}
			free (tmp);
			tmp = NULL;
			return (1);
		}
		free (tmp);
		tmp = NULL;
		i++;
	}
	prompt[i] = NULL;
	data->prompt = prompt;
	return (0);
}