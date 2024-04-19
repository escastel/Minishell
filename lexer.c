/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:38:48 by escastel          #+#    #+#             */
/*   Updated: 2024/04/19 12:23:47 by lcuevas-         ###   ########.fr       */
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

	command = ft_calloc(1, ((sizeof(t_cmds))));
	command->full_cmd = ft_calloc(1, (sizeof(char **)));
	command->exc_path = ft_calloc(1, (sizeof(char *)));
	command->outfile = dup(STDOUT_FILENO); // por probarlo de guardar el fd desde el principio
	command->infile = dup(STDIN_FILENO);
	return (command);
}

void	ft_inoutfileator(t_cmds *command, char **aux, char **line)
{
	printf("INTRAINOUT1: %s\n", aux[0]);
	if (*aux[0] == '<')
	{
		if (ft_strlen(aux[0]) == 1)
		{
			*aux = ft_take_first_word(&*line);
			printf("INTRAINOUT1: %s\n", aux[0]);
			command->infile = open(*aux, O_RDONLY, 00444);
			printf("IN: %d\n", command->infile);
			*aux = ft_take_first_word(&line[0]);
			return ;
		}
		else
		{
			*aux += 1;
			if (*aux[0] == '<')
			{
				printf("HEREDOC: \n");
			}
			else
			{
				printf("INTRAINOUT1: %s\n", aux[0]);
				command->infile = open(*aux, O_RDONLY, 00444);
				printf("IN: %d\n", command->infile);
				*aux = ft_take_first_word(&line[0]);
				return ;
			}
		}
	}
	else
	{
		if (ft_strlen(aux[0]) == 1)
		{
			*aux = ft_take_first_word(&*line);
			printf("INTRAINOUT1: %s\n", aux[0]);
			command->outfile = open(*aux, O_WRONLY | O_CREAT | O_TRUNC, 00644);
			printf("IN: %d\n", command->infile);
			*aux = ft_take_first_word(&line[0]);
			return ;
		}
		else
		{
			*aux += 1;
			if (*aux[0] == '>')
			{
				printf("APEND: \n");
			}
			else
			{
				printf("INTRAINOUT1: %s\n", aux[0]);
				command->outfile = open(*aux, O_WRONLY | O_CREAT | O_TRUNC, 00644);
				printf("IN: %d\n", command->infile);
				*aux = ft_take_first_word(&line[0]);
				return ;
			}
		}
	}
}


int	ft_rellenator(t_cmds *command, char *line)
{
	int		i;
	char	*aux;

	i = 0;
	aux = ft_take_first_word(&line);
	if (!aux) //este igual sobra
		return (1);
	while (ft_strlen(aux) != 0)
	{
		while (aux[0] == '<' || aux[0] == '>')
			ft_inoutfileator(command, &aux, &line);
		if (ft_strlen(aux) != 0)
		{

			command->full_cmd[i] = ft_strdup(aux);
			printf("COMMNAD: %s\n", command->full_cmd[i]);
			free (aux);
			i += 1;
		}
		aux = ft_take_first_word(&line);
	}
	command->full_cmd[i] = 0;
	free (aux);
	return (0);
}

int	ft_noduler(t_data *data, char **arr)
{
	int		i;
	t_cmds	*command;
	t_list	*new;

	command = ft_new_cmd_node();
	if (!command)
		return (1);
	new = ft_lstnew(command);
	if (!new)
		return (1);
	data->cmd = new;
	i = 1;
	while (arr[i])
	{
		command = ft_new_cmd_node();
		if (!command)
			return (1);
		new = ft_lstnew(command);
		ft_lstadd_back(&data->cmd, new);
		i += 1;
	}
	return (0);
}

int	lexer(t_data *data, char *line)
{
	char	**tmp;
	t_list	*aux;
	int		i;

	i = 0;
	tmp = ft_split(line, '|'); //se le puede meter if al tmp? nu ze si merece la pena
	if (ft_noduler(data, tmp))
		return (1);
	aux = data->cmd;
	while (tmp[i])
	{
		if (ft_rellenator(aux->content, tmp[i]))
			return (1);
		i += 1;
		aux = aux->next;
	}
	i = 0; // si se va de lineas se puede hacer un buclecito de liberar arrais dobles ya en general pa to las veces que haga falta
	while (tmp[i])
	{
		free(tmp[i]);
		i += 1;
	}
	free(tmp);
	return (0);
}
