/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:56:36 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/05/07 11:20:10 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_noduler_pipe(t_data *data, t_list **aux, int *j, int *i)
{
	((t_cmds *)(*aux)->content)->full_cmd[*j] = NULL;
	ft_next_node(data);
	*j = 0;
	free (data->prompt[*i]);
	*i += 1;
	(*aux) = (*aux)->next;
	((t_cmds *)(*aux)->content)->full_cmd = ft_tmp_reservator(data);
}

static void	ft_nodule_2(t_data *data, t_list *aux, int *i, int *j)
{
	expander(data, *i);
	((t_cmds *)aux->content)->full_cmd[*j] = data->prompt[*i];
	*i += 1;
	*j += 1;
	((t_cmds *)aux->content)->full_cmd[*j] = NULL;
}

static void	ft_noduler(t_data *data)
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
		if (((t_cmds *)aux->content)->infile == -1)
			return (free (data->prompt));
	}
	free (data->prompt);
	return ;
}

int	parser(t_data *data)
{
	int	i;

	if (data->prompt[0][0] == '|')
	{
		i = -1;
		while (data->prompt[++i])
			free(data->prompt[i]);
		free (data->prompt);
		error_msg("michishell: syntax error near unexpected token");
		data->status = 258;
		return (1);
	}
	ft_new_cmd(data);
	ft_noduler(data);
	return (0);
}
