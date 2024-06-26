/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:53:22 by escastel          #+#    #+#             */
/*   Updated: 2024/05/07 13:06:52 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_no_file_or_dir(t_data *data, int *i)
{
	printf("%s: No such file or directory\n", data->prompt[*i]);
	while (data->prompt[*i])
	{
		if (data->prompt[*i][0] == '|')
			break ;
		free (data->prompt[*i]);
		*i += 1;
	}
}

static int	ft_redir_out(t_data *data, t_cmds *aux, int i)
{
	if (ft_strlen(data->prompt[i]) == 2)
	{
		aux->outfile = open(data->prompt[++i],
				O_WRONLY | O_CREAT | O_APPEND, 00644);
		free(data->prompt[i - 1]);
		free(data->prompt[i]);
		return (++i);
	}
	else
	{
		aux->outfile = open(data->prompt[++i],
				O_WRONLY | O_CREAT | O_TRUNC, 00644);
		free(data->prompt[i - 1]);
		free(data->prompt[i]);
		return (++i);
	}
}

static int	ft_redir_in(t_data *data, t_cmds *aux, int i)
{
	if (ft_strlen(data->prompt[i]) == 2)
	{
		heredoc(data, aux, ++i);
		free(data->prompt[i - 1]);
		free(data->prompt[i]);
		return (++i);
	}
	else
	{
		aux->infile = open(data->prompt[++i], O_RDONLY, 00444);
		free(data->prompt[i - 1]);
		if (aux->infile == -1)
		{
			ft_no_file_or_dir(data, &i);
			return (i);
		}
		free(data->prompt[i]);
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
