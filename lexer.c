/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:38:48 by escastel          #+#    #+#             */
/*   Updated: 2024/04/05 18:11:11 by lcuevas-         ###   ########.fr       */
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
	command->infile = (int )malloc(sizeof(int));
	command->outfile = (int )malloc(sizeof(int));
	return (command);
}

void	lexer(t_data *data, char *line)
{
	int		i;
	char	*aux;
	t_cmds	*command;
	t_list	*new;

	i = 0;
//	command = ft_new_cmd_node();
	command = (t_cmds *)malloc(sizeof(t_cmds));
	new = ft_lstnew(command);
	data->cmd = new;
//	ft_lstadd_back(&data->cmd, new);
	command->full_cmd = ft_calloc(1, 10*(sizeof(char **))); // problema del tamano de esto
	while (ft_strlen(line) != 0)
	{
		aux = ft_take_first_word(&line);
		if (aux[0] == '|')
		{
			command = (t_cmds *)malloc(sizeof(t_cmds));
			new = ft_lstnew(command);
			ft_lstadd_back(&data->cmd, new);
			i = 0;
			// faltaria señalizar el outfile y el infile. al parser?
		}
		else if (ft_strlen(aux) != 0)
		{
			command->full_cmd[i] = ft_calloc(1, ft_strlen(aux));
			command->full_cmd[i] = aux;
			i += 1;
		}
	}
}
