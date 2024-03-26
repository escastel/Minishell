/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:38:48 by escastel          #+#    #+#             */
/*   Updated: 2024/03/26 17:48:50 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_singlequote(char **argv, char **str, int j)
{
	(*str)[j] = **argv;
	*argv += 1;
	j += 1;
	while (**argv != 39)
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
	while (**argv != '"')
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
		if (**argv == '"')
			j = ft_doublequote(&(*argv), &str, j);
		if (**argv == 39)
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

t_cmds	*ft_fill_command(char *line)
{
	t_cmds	*command;
	char	*aux;
	int		i;
	int		n;

	i = 0;
	n = ft_strlen(line);
	command = ft_calloc(1, sizeof(t_cmds));
	command->full_cmd = ft_calloc(1, 10*(sizeof(char **)));
	while (ft_strlen(line) != 0)
	{
		aux = ft_take_first_word(&line);
		command->full_cmd[i] = ft_calloc(1, ft_strlen(aux));
		command->full_cmd[i] = aux;
		i += 1;
	}
	return (command);
}

void	lexer(t_data *data, char *line)
{
	t_cmds	*command;
	int		i;

	command = ft_fill_command(line);
	data->cmd[0] = command;
	printf("%s\n", "printCOMMAND");
	i = 0;
	while (command->full_cmd[i])
	{
		printf("%s\n", command->full_cmd[i]);
		i += 1;
	}
	printf("%s\n", "printDATA->CMD");
	i = 0;
	while (data->cmd[0]->full_cmd[i])
	{
		printf("%s\n", data->cmd[0]->full_cmd[i]);
		i += 1;
	}
}
