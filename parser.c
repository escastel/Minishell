/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:56:36 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/04/29 13:32:53 by lcuevas-         ###   ########.fr       */
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
	command->full_cmd = NULL; //estos mallocs antes eran de otra manera
	command->exc_path = NULL;
	command->outfile = 1;
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

int	ft_redir_out(t_data *data, t_cmds *aux, int i)
{
	if (ft_strlen(data->prompt[i]) == 2)
	{
		aux->outfile = open(data->prompt[++i],
				O_WRONLY | O_CREAT | O_APPEND, 00644);
		return (++i);
	}
	else
	{
		aux->outfile = open(data->prompt[++i],
				O_WRONLY | O_CREAT | O_TRUNC, 00644);
		return (++i);
	}
}

int	ft_redir_in(t_data *data, t_cmds *aux, int i)
{
	if (ft_strlen(data->prompt[i]) == 2)
	{
		heredoc(data, aux, ++i);
		return (++i);
	}
	else
	{
		aux->infile = open(data->prompt[++i], O_RDONLY, 00444);
		return (++i);
	}
}

int	ft_redir(t_data *data, t_cmds *aux, int i)
{
	if (data->prompt[i][0] == '<')
		return (ft_redir_in(data, aux, i));
	else if (data->prompt[i][0] == '>')
		return (ft_redir_out(data, aux, i));
	return (i);
}

char **ft_tmp_reservator(t_data *data)
{
	char	**tmp;
	int		i;

	i = 0;

	while (data->prompt[i])
		i += 1;
	tmp = ft_calloc(i + 1, sizeof(char *));
	return (tmp);
}

void	ft_noduler_pipe(t_data *data, t_list **aux, int *j, int *i)
{
	((t_cmds *)(*aux)->content)->full_cmd[*j] = NULL;
	ft_next_node(data);
	*j = 0;
	*i += 1;
	(*aux) = (*aux)->next;
	((t_cmds *)(*aux)->content)->full_cmd = ft_tmp_reservator(data);
}

void	ft_nodule_2(t_data *data, t_list *aux, int *i, int *j)
{
	expander(data, *i);
	((t_cmds *)aux->content)->full_cmd[*j] = data->prompt[*i]; //se podria usar un strdup si hay problemas con als reseervas
	*i += 1;
	*j += 1;
	((t_cmds *)aux->content)->full_cmd[*j] = NULL;
}

void	ft_noduler(t_data *data)
{
	t_list	*aux;
	int		i;
	int		j;

	aux = data->cmd;
	i = 0;
	j = 0;
	((t_cmds *)aux->content)->full_cmd = ft_tmp_reservator(data);
	while (data->prompt[i])
	{
		if ((data->prompt[i][0] == '<') || (data->prompt[i][0] == '>'))
			i = ft_redir(data, aux->content, i);
		else if (data->prompt[i][0] == '|')
			ft_noduler_pipe(data, &aux, &j, &i);
		else
			ft_nodule_2(data, aux, &i, &j);
	}
	return ;
}

/* void	ft_noduler(t_data *data)
{
	t_list	*aux;
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	aux = data->cmd;
	tmp = ft_tmp_reservator(data);
	while (data->prompt[i])
	{
		if ((data->prompt[i][0] == '<') || (data->prompt[i][0] == '>'))
			i = ft_redir(data, aux->content, i);
		else if (data->prompt[i][0] == '|')
		{
			ft_noduler_pipe(data, aux, tmp, &j);
			tmp = ft_tmp_reservator(data);
			i += 1;
		}
		else
			ft_nodule_2(data, tmp, &i, &j);
	}
	tmp[j] = NULL;
	((t_cmds *)aux->content)->full_cmd = tmp;
	return ;
} */

/* void	ft_noduler(t_data *data) //ESTA ES LA ORIGINAL con medio cambio que tambien dunciona, peor por reducir
{
	t_list	*aux;
	int		i;
	int		j;

	aux = data->cmd;
	i = 0;
	j = 0;
	((t_cmds *)aux->content)->full_cmd = ft_tmp_reservator(data);
	while (data->prompt[i])
	{
		if ((data->prompt[i][0] == '<') || (data->prompt[i][0] == '>'))
			i = ft_redir(data, aux->content, i);
 		else if (data->prompt[i][0] == '|')
		{
			((t_cmds *)aux->content)->full_cmd[j] = NULL;
			ft_next_node(data);
			j = 0;
			i += 1;
			aux = aux->next;
			((t_cmds *)aux->content)->full_cmd = ft_tmp_reservator(data);
		}
		else
			ft_nodule_2(data, aux, &i, &j);
	}
	return ;
} */

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
