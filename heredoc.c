/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:39:00 by escastel          #+#    #+#             */
/*   Updated: 2024/04/25 16:07:46 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Puede que tenga que anadir un mensaje de error 

static void	heredoc_control(t_cmds *cmd, char *limit)
{
	char	*eof;
	char	*line;
	int		heredoc_tmp;

	eof = ft_strjoin(limit, "\n");
	heredoc_tmp = open("heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (12)
	{
		printf("> ");
		line = get_next_line(0);
		if (!line)
			return ;
		if (!ft_strncmp(eof, line, ft_strlen(line)))
		{
			free (eof);
			free (line);
			break ;
		}
		ft_putstr_fd(line, heredoc_tmp);
		free(line);
	}
	close(heredoc_tmp);
	cmd->infile = open("heredoc.tmp", O_RDONLY);
}

void	heredoc(t_data *data, t_cmds *cmd)
{
	if (cmd->full_cmd[1])
	{
		data->heredoc = 1;
		heredoc_control(cmd, cmd->full_cmd[1]);
	}
	else
		return ;
}
