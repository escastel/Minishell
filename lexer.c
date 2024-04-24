/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:38:48 by escastel          #+#    #+#             */
/*   Updated: 2024/04/24 12:37:01 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_singlequote(char **argv, char **str, int j)
{
	(*str)[j] = **argv;
	*argv += 1;
	j += 1;
	while (**argv != '\'')
	{
		(*str)[j] = **argv;
		*argv += 1;
		j += 1;
	}
	(*str)[j] = **argv;
	*argv += 1;
	j += 1;
	return (j);
}

int	ft_doublequote(char **argv, char **str, int j)
{
	(*str)[j] = **argv;
	*argv += 1;
	j += 1;
	while (**argv != '\"')
	{
		(*str)[j] = **argv;
		*argv += 1;
		j += 1;
	}
	(*str)[j] = **argv;
	*argv += 1;
	j += 1;
	return (j);
}

int	ft_backlashes(char **argv, char **str, int j)
{
	while (**argv == '\\')
	{
		(*str)[j] = (*(*argv + 1));
		*argv += 2;
		j += 1;
	}
	return (j);
}

int	ft_quotes(char **argv, char **str, int j)
{
	if (**argv == '\"')
		j = ft_doublequote(&(*argv), &(*str), j);
	if (**argv == '\'')
		j = ft_singlequote(&(*argv), &(*str), j);
	return (j);
}

char	*ft_take_first_word(char **line)
{
	int		j ;
	char	*str;
	char	*ret;

	str = ft_calloc(1, ft_strlen(*line));
	j = 0;
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
		ret = ft_strdup(str);
		free (str);
		return (ret);
	}
	while (**line != ' ' && **line)
	{
		j = ft_backlashes(&(*line), &str, j); //esta se puede ir a la revergadura
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
	str[j] = 0;
	ret = ft_strdup(str);
	free (str);
	return (ret);
}

char	**ft_split_words(char *line)
{
	char	**aux;
//	char	**ret;
	char	*tmp;
	int		i;

	i = 0;
	aux = (char **)malloc(sizeof(char *) * 20 + 1); //reserva dinamica?
	tmp = ft_take_first_word(&line);
	while (ft_strlen(tmp) != 0)
	{
		aux[i] = ft_strdup(tmp);
		free(tmp);
		i += 1;
		tmp = ft_take_first_word(&(line));
	}
	aux[i] = 0;
/* 	ret = (char **)malloc(sizeof(char *) * 20 + 1); //reserva dinamica?
	ret = ft_subsplit(aux); */
	return (aux);
}

int	lexer(t_data *data, char *line)
{
	char	**tmp;
	int		i;


	i = 0;
	tmp = ft_split_words(line);
	data->prompt = tmp;
//	tmp = subsplit?
// llamar expander aquu'i y despues al parse?
/* 	expander(data);
	printf("expander\n"); podemos meterlo aqu'i dentro*/
	return (0);
}
