/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:38:48 by escastel          #+#    #+#             */
/*   Updated: 2024/04/25 15:35:42 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_tokens(char **line, char **tmp)
{
	char	*str;
	int		j;

	j = 0;
	str = ft_calloc(1, ft_strlen(*line));
	while (**line == 32 || (**line >= 9 && **line <= 13))
		*line += 1;
	if (**line == '<' || **line == '>' || **line == '|')
	{
		str[j] = **line;
		*line += 1;
		j += 1;
		if (**line == '<' || **line == '>')
		{
			str[j] = **line;
			*line += 1;
			j += 1;
		}
		*tmp = ft_strdup(str);
		free (str);
		str = NULL;
		return (1);
	}
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
		data->prompt[i] = NULL;
		if (ft_strcmp(tmp, "", ft_strlen(tmp)))
			data->prompt[i] = ft_strdup(tmp);
		printf("%s\n", tmp);
		free (tmp);
		tmp = NULL;
		i++;
	}
	data->prompt[i] = 0;
	return (0);
}
