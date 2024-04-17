/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:38:48 by escastel          #+#    #+#             */
/*   Updated: 2024/04/10 18:59:28 by escastel         ###   ########.fr       */
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

t_cmds	*ft_new_cmd_node(void)
{
	t_cmds		*command;

	command = (t_cmds *)malloc(sizeof(t_cmds));
	command->full_cmd = (char **)malloc(sizeof(char **));
	command->exc_path = (char *)malloc(sizeof(char *));
	command->outfile = dup(STDOUT_FILENO); // por probarlo de guardar el fd desde el principio
	command->infile = dup(STDIN_FILENO);
	command->builtin = 0;
	return (command);
}

void	lexer(t_data *data, char *line)
{
	int		i;
	char	*aux;
	t_cmds	*command;
	t_list	*new;

	command = ft_new_cmd_node();
	new = ft_lstnew(command);
	data->cmd = new;
	command->full_cmd = ft_calloc(1, 10*(sizeof(char **))); // problema del tamano de esto
	i = 0;
	while (ft_strlen(line) != 0)
	{
		aux = ft_take_first_word(&line);
		if (aux[0] == '|') // habr'a que hacer funcion tokenizator
		{
			command = ft_new_cmd_node();
			new = ft_lstnew(command);
			ft_lstadd_back(&data->cmd, new);
			i = 0;
		}
		else if (ft_strlen(aux) != 0)
		{
			command->full_cmd[i] = ft_strdup(aux);
			i += 1;
		}
	}
}
