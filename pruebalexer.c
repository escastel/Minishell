/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:38:48 by escastel          #+#    #+#             */
/*   Updated: 2024/04/11 13:23:44 by lcuevas-         ###   ########.fr       */
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
	char	*ret;

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
	ret = ft_strdup(str);
	free (str);
	return (ret);
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

void	ft_rellenator(t_cmds *command, char *line)
{
	int		i;
	char	*aux;

	i = 0;
	aux = ft_take_first_word(&line);
	while (ft_strlen(aux) != 0)
	{
		if (ft_strlen(aux) != 0)
		{
			command->full_cmd[i] = ft_strdup(aux);
			free (aux);
			i += 1;
		}
		aux = ft_take_first_word(&line);
	}
	free (aux);
}

void	ft_noduler(t_data *data, char **arr)
{
	int		i;
	t_cmds	*command;
	t_list	*new;

	command = ft_new_cmd_node();
	new = ft_lstnew(command);
	data->cmd = new;
	i = 1;
	while (arr[i])
	{
		command = ft_new_cmd_node();
		new = ft_lstnew(command);
		ft_lstadd_back(&data->cmd, new);
		i += 1;
	}
}

void	lexer(t_data *data, char *line)
{
	char	**tmp;
	t_list	*aux;
	int		i;

	i = 0;
	tmp = ft_split(line, '|');
	ft_noduler(data, tmp);
	aux = data->cmd;
	while (tmp[i])
	{
		ft_rellenator(aux->content, tmp[i]);
		i += 1;
		aux = aux->next;
	}
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i += 1;
	}
	free(tmp);
}
