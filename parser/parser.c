/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:56:36 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/05/03 12:55:10 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_noduler_pipe(t_data *data, t_list **aux, int *j, int *i)
{
	((t_cmds *)(*aux)->content)->full_cmd[*j] = NULL;
	ft_next_node(data);
	*j = 0;
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
	}
	return ;
}

int	parser(t_data *data)
{
	ft_new_cmd(data);
	ft_noduler(data);
	if (((t_cmds *)data->cmd->content)->full_cmd[0] == NULL)
	{
		error_msg("michishell: syntax error near unexpected token");
		data->status = 258;
		return (1);
	}
	return (0);
}
