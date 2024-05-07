/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:38:48 by escastel          #+#    #+#             */
/*   Updated: 2024/05/07 15:24:18 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	clean_prompt(char ***prompt, char **tmp)
{
	char	**aux;
	int		i;

	i = 0;
	aux = *prompt;
	if (aux)
	{
		if (aux[i])
		{
			i = -1;
			while (aux[++i])
				free (aux[i]);
		}
		free (aux);
	}
	if (*tmp)
		free (*tmp);
}

static int	tokens(t_data *data, char **line, char **tmp)
{
	int	flag;

	while (**line == 32 || (**line >= 9 && **line <= 13))
		*line += 1;
	flag = ft_tokens_mayor(data, line, tmp);
	if (flag)
		return (flag);
	flag = ft_tokens_minor(data, line, tmp);
	if (flag)
		return (flag);
	flag = ft_tokens_pipe(data, line, tmp);
	if (flag)
		return (flag);
	return (0);
}

static int	ft_take_first_word(t_data *data, char **line, char **tmp)
{
	char	*str;
	int		flag;

	flag = tokens(data, line, tmp);
	if (flag)
		return (flag);
	data->j = 0;
	str = ft_calloc(1, ft_strlen(*line));
	while (**line != ' ' && **line)
	{
		if (ft_quotes_and_lashes(data, &(*line), &str))
			return (free (str), 1);
		if (**line == '<' || **line == '>' || **line == '|')
			break ;
		if (**line && **line != ' ' && **line != '\'' && **line != '\"')
		{
			str[data->j++] = **line;
			*line += 1;
		}
	}
	while (**line == 32 || (**line >= 9 && **line <= 13))
		*line += 1;
	str[data->j] = '\0';
	*tmp = ft_strdup(str);
	return (free (str), 0);
}

int	lexer(t_data *data, char *line)
{
	char	*tmp;

	data->i = 0;
	tmp = NULL;
	data->prompt = ft_calloc(ft_strlen(line) + 1, sizeof(char *));
	while (*line)
	{
		if (ft_take_first_word(data, &line, &tmp) == 1)
		{
			clean_prompt(&data->prompt, &tmp);
			return (1);
		}
		if (tmp && ft_strncmp(tmp, "", ft_strlen(tmp)))
			data->prompt[data->i] = ft_strdup(tmp);
		else
		{
			clean_prompt(&data->prompt, &tmp);
			return (1);
		}
		if (tmp)
			free (tmp);
		tmp = NULL;
		data->i++;
	}
	return (0);
}
