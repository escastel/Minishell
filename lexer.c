/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:38:48 by escastel          #+#    #+#             */
/*   Updated: 2024/03/28 09:47:30 by lcuevas-         ###   ########.fr       */
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

char	*ft_take_first_word(char **argv)
{
	int		j;
	char	*str;

	str = ft_calloc(1, ft_strlen(*argv));
	j = 0;
	while (**argv == 32 || (**argv >= 9 && **argv <= 13))
		*argv += 1;
	while (**argv != ' ' && **argv)
	{
		j = ft_backlashes(&(*argv), &str, j);
		if (**argv == '\"')
			j = ft_doublequote(&(*argv), &str, j);
		if (**argv == '\'')
			j = ft_singlequote(&(*argv), &str, j);
		if (**argv != ' ')
		{
			str[j] = **argv;
			*argv += 1;
			j += 1;
		}
	}
	str[j] = 0;
	return (str);
}

void	lexer(t_data *data, char *line)
{
	int		i;
	char	*aux;
	t_cmds	*command;

	i = 0;
	command = ft_calloc(1, sizeof(t_cmds));
	command->full_cmd = ft_calloc(1, 10*(sizeof(char **))); // problema del tamano de esto
	while (ft_strlen(line) != 0)
	{
		aux = ft_take_first_word(&line);
		command->full_cmd[i] = ft_calloc(1, ft_strlen(aux));
		command->full_cmd[i] = aux;
		i += 1;
	}
	data->cmd[0] = command;
}
// el segmentation lo da con el printf, es decir, rellena pero mete mierda al final
