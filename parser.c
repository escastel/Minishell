/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:56:36 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/04/25 16:44:47 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_path(t_data *data)
{
	char	*envp_path;
	int		i;

	i = 0;
	envp_path = 0;
	while (data->env[i])
	{
		if (strncmp(data->env[i], "PATH=", 5) == 0)
		{
			envp_path = data->env[i] + 5;
			break ;
		}
		i++;
	}
	if (!envp_path)
		return (1); //ft_error();
	data->cmd_path = ft_split (envp_path, ':');
	return (0);
}

t_cmds	*ft_new_cmd_node(void)
{
	t_cmds		*command;

	command = ft_calloc(1, ((sizeof(t_cmds))));
	command->full_cmd = ft_calloc(1, (sizeof(char **)));
	command->exc_path = ft_calloc(1, (sizeof(char *)));
	command->outfile = 1; // por probarlo de guardar el fd desde el principio
	command->infile = 0;
	return (command);
}

void	ft_next_node(t_data *data)
{
	t_cmds	*command;
	t_list	*new;

	command = ft_new_cmd_node();
	new = ft_lstnew(command);
	ft_lstadd_back(&data->cmd, new);
}

int	ft_redir(t_data *data,t_cmds *aux, int i)
{
	if (data->prompt[i][0] == '<')
	{
		if (data->prompt[i][1] == '<')
		{
			printf("HEREDOC\n");
			return (++i);
		}
		if (data->prompt[i][1])
		{
			aux->infile = open(data->prompt[++i], O_RDONLY, 00444);
			return (++i);
		}
	}
	else if (data->prompt[i][0] == '>')
	{
		if (data->prompt[i][1] == '>')
		{
			aux->outfile = open(data->prompt[++i], O_WRONLY | O_CREAT | O_APPEND, 00644);
			return (++i);
		}
		if (data->prompt[i][1])
		{
			aux->outfile = open(data->prompt[++i], O_WRONLY | O_CREAT | O_TRUNC, 00644);
			return (++i);
		}
	}
	return (++i); //meterle una comprobación de errores antes de los returns? cambiar esta logica creo yo
}

void	ft_noduler(t_data *data)
{
	t_list	*aux;
	int		i;
	int		j;

	i = 0;
	j = 0;
	aux = data->cmd;
	((t_cmds *)aux->content)->full_cmd[j] = NULL;
	while (data->prompt[i])
	{
		printf("PROMPT: %s\n", data->prompt[i]);
		if ((data->prompt[i][0] == '<') || (data->prompt[i][0] == '>'))
			i = ft_redir(data, aux->content, i);
 		else if (data->prompt[i][0] == '|')
		{
			ft_next_node(data);
			j = 0;
			i += 1;
			aux = aux->next;
		}
		else
		{
			((t_cmds *)aux->content)->full_cmd[j] = expander(data, i);
			printf("%s\n", ((t_cmds *)aux->content)->full_cmd[j]);
			i += 1;
			j += 1;
			((t_cmds *)aux->content)->full_cmd[j] = NULL;
		}
	}
	printf("%d\n", ((t_cmds *)aux->content)->infile);
	return ;
}

void	ft_new_cmd(t_data *data)
{
	t_list	*new;
	t_cmds	*command;

	command = ft_new_cmd_node();
	new = ft_lstnew(command);
	data->cmd = new;
}

int	parser(t_data *data)
{
	ft_new_cmd(data);
	ft_path(data);
	ft_noduler(data);
	return (0);
}
