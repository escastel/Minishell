/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:43:40 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/05/03 17:32:57 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_delete_cmd(void *content)
{
	t_cmds	*cmd;
	int		i;

	cmd = (t_cmds *)content;
	i = 0;
	while (cmd->full_cmd[i])
	{
		free (cmd->full_cmd[i]);
		cmd->full_cmd[i] = NULL;
		i++;
	}
	if (cmd->full_cmd)
		free (cmd->full_cmd);
	if (cmd->exc_path)
		free (cmd->exc_path);
	if (cmd->infile != 0)
		close(cmd->infile);
	if (cmd->outfile != 1)
		close(cmd->outfile);
	if (cmd)
		free (cmd);
}

void	ft_clean_path(t_data *data)
{
	int	i;

	i = 0;
	if (data->cmd_path)
	{
		while (data->cmd_path[i])
		{
			free (data->cmd_path[i]);
			data->cmd_path[i] = NULL;
			i++;
		}
		free (data->cmd_path);
	}
}

void	clean_cmd(t_data *data)
{
	int	i;

	i = 3;
	while (i <= 255)
	{
		close (i);
		i += 1;
	}
	ft_lstclear(&data->cmd, &ft_delete_cmd);
	if (data->cmd)
		free (data->cmd);
	ft_clean_path(data);
}
