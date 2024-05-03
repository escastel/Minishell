/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:53:22 by escastel          #+#    #+#             */
/*   Updated: 2024/05/03 12:54:29 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_redir_out(t_data *data, t_cmds *aux, int i)
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

static int	ft_redir_in(t_data *data, t_cmds *aux, int i)
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
