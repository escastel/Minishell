/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:39:00 by escastel          #+#    #+#             */
/*   Updated: 2024/04/29 12:41:22 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Puede que tenga que anadir un mensaje de error 

static void	heredoc_control(t_cmds *cmd, char *limit)
{
	char	*eof;
	char	*line;
	int		pipefd[2];

	pipe(pipefd);
	if (pipefd < 0)
		exit(1); //ft error
	//cosillas con la se;al pal heredoc de la se;al
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
	{
		/* data->heredoc = 1; */
		heredoc_control(cmd, data->prompt[i]);
	}
	else
		return ;
}

/* void	ft_heredoc(t_cmds *command, char *here)
{
	char	*here_line;

	command->infile = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		write(1, "> ", 2);
		here_line = get_next_line2(0);
		if (ft_strncmp(here_line, here, ft_strlen(here) + 1) == 10)
		{
			free (here_line);
			break ;
		}
		write (command->infile, here_line, ft_strlen(here_line));
		free (here_line);
	}
	close(command->infile);
	command->infile = open(".tmp", O_RDONLY);
} */
