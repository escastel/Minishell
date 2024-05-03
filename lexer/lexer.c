/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:38:48 by escastel          #+#    #+#             */
/*   Updated: 2024/05/03 20:18:32 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	clean_prompt_and_tmp(char ***prompt, char **tmp)
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
	printf("TMP: %p\n", *tmp);
	if (*tmp)
		free (*tmp);
}

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

static int	ft_take_first_word(t_data *data, char **line, char **tmp)
{
	char	*str;
	int		flag;

	flag = tokens(line, tmp);
	if (flag)
		return (flag);
	data->j = 0;
	str = ft_calloc(1, ft_strlen(*line));
	while (**line != ' ' && **line)
	{
		data->j = ft_backlashes(&(*line), &str, data->j);
		data->j = ft_quotes(&(*line), &str, data->j);
		if (**line == '<' || **line == '>' || **line == '|')
			break ;
		if (**line != ' ')
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
		if (ft_take_first_word(data, &line, &tmp) == 258)
		{
			printf("holi?\n");
			clean_prompt_and_tmp(&data->prompt, &tmp);
			data->status = 258;
			return (1);
		}
		if (tmp && ft_strncmp(tmp, "", ft_strlen(tmp)))
			data->prompt[data->i] = ft_strdup(tmp);
		else
		{
			clean_prompt_and_tmp(&data->prompt, &tmp);
			return (1);
		}
		free (tmp);
		data->i++;
	}
	return (0);
}
