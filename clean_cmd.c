/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:43:40 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/04/29 13:41:22 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free (cmd->full_cmd);
	if (cmd->exc_path)
		free (cmd->exc_path);
	cmd->exc_path = NULL;
	if (cmd->infile != 0)
		close(cmd->infile);
	if (cmd->outfile != 1)
		close(cmd->outfile);
}

void	ft_clean_path(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmd_path[i])
	{
		free (data->cmd_path[i]);
		data->cmd_path[i] = NULL;
		i++;
	}
	free (data->cmd_path);
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
	free (data->cmd);
	ft_clean_path(data);
}
