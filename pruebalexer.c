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

//	str = ft_calloc(1, ft_strlen(*argv));
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

/* void	ft_rellenator(t_cmds *command, char *line)
{
	int		i;
	char	*aux;

	i = 0;
	while (ft_strlen(line) != 0)
	{
		printf("%d\n", ft_strlen(line));
		printf("%s\n", line);
		aux = ft_take_first_word(&line);
//		printf("%s\n", line);
		if (ft_strlen(aux) != 0)
		{
			command->full_cmd[i] = ft_calloc(1, ft_strlen(aux));
			command->full_cmd[i] = aux;
			i += 1;
		}
	}
} */

void	ft_rellenator(t_cmds *command, char *line)
{
	int		i;
	char	*aux;

	i = 0;
	aux = ft_take_first_word(&line);
	while (ft_strlen(aux) != 0)
	{
//		printf("UNCICLORELLENATOR\n");
//		printf("%d", ft_strlen(aux));
//		printf("%s\n ", aux);
//		printf("%s\n", line);
		if (ft_strlen(aux) != 0)
		{
//			printf("AUX: %s\n", aux);
			command->full_cmd[i] = aux;
//			printf("CMD: %s\n", command->full_cmd[i]);
			i += 1;
		}
		aux = ft_take_first_word(&line);
	}
	printf("ENDRELLENATOR\n");
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
//	printf("%s\n", tmp[0]);
//	printf("%s\n", tmp[1]);
	aux = data->cmd;
	while (aux)
	{
		ft_rellenator(aux->content, tmp[i]);
		i += 1;
//		printf("%s\n", ((t_cmds *)data->cmd->content)->full_cmd[0]);
		printf("%s\n", ((t_cmds *)aux->content)->full_cmd[0]);
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

/* void	lexer(t_data *data, char *line)
{
	int		i;
	char	*aux;
	t_cmds	*command;
	t_list	*new;

	i = 0;
	command = ft_new_cmd_node();
	new = ft_lstnew(command);
	data->cmd = new;
	command->full_cmd = ft_calloc(1, 10*(sizeof(char **))); // problema del tamano de esto
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
			command->full_cmd[i] = ft_calloc(1, ft_strlen(aux));
			command->full_cmd[i] = aux;
			i += 1;
		}
	}
} */
