/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:39:00 by escastel          #+#    #+#             */
/*   Updated: 2024/05/02 19:27:11 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	heredoc_control(t_cmds *cmd, char *limit)
{
	char	*eof;
	char	*line;
	int		pipefd[2];

	pipe(pipefd);
	if (pipefd < 0)
		exit(1);
	eof = ft_strjoin(limit, "\n");
	while (12)
	{
		write (1, "> ", 2);
		line = get_next_line2(0);
		if (!line)
			return ;
		if (!ft_strncmp(eof, line, ft_strlen(line)))
		{
			free (eof);
			free (line);
			break ;
		}
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
	close(pipefd[1]);
	cmd->infile = pipefd[0];
}

void	heredoc(t_data *data, t_cmds *cmd, int i)
{
	if (data->prompt[i])
		heredoc_control(cmd, data->prompt[i]);
	else
		return ;
}
