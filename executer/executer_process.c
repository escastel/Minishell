/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:36:54 by escastel          #+#    #+#             */
/*   Updated: 2024/05/03 12:37:33 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parent(t_data *data, t_list	*cmd)
{
	data->status = 0;
	ft_file_or_directory(data, cmd);
	if (builtins_control(data, ((t_cmds *)cmd->content)->full_cmd, 1) == 0)
	{
		if (ft_command_filter(data, cmd) == 1)
			data->status = 127;
	}
	if (cmd->next)
	{
		close(data->pipe[1]);
		if (dup2(data->pipe[0], STDIN_FILENO) == -1)
			return ;
		return ;
	}
	return ;
}

void	ft_child_redir(t_data *data, t_list *cmd)
{
	if ((((t_cmds *)cmd->content)->infile) != STDIN_FILENO)
		dup2((((t_cmds *)cmd->content)->infile), STDIN_FILENO);
	if (cmd->next)
	{
		if ((((t_cmds *)cmd->content)->outfile) != STDOUT_FILENO)
			dup2((((t_cmds *)cmd->content)->outfile), STDOUT_FILENO);
		else if (dup2(data->pipe[1], STDOUT_FILENO) == -1)
			return ;
	}
	else
		dup2(((t_cmds *)cmd->content)->outfile, STDOUT_FILENO);
}

void	ft_child(t_data *data, t_list *cmd, int flag)
{
	ft_child_redir(data, cmd);
	if (flag == 0)
	{
		builtins_control(data, ((t_cmds *)cmd->content)->full_cmd, 0);
		exit(0);
	}
	ft_path(data);
	if (flag == 1)
	{
		if (ft_command_filter(data, cmd) == 0)
		{
			if (execve(((t_cmds *)cmd->content)->exc_path,
					((t_cmds *)cmd->content)->full_cmd, data->env) == -1)
				exit (EXIT_FAILURE);
		}
	}
	ft_no_cmd(data, ((t_cmds *)cmd->content)->full_cmd);
	exit(0);
}

void	ft_xone_child(t_data *data, t_list *cmd)
{
	ft_child_redir(data, cmd);
	if (execve(((t_cmds *)cmd->content)->exc_path,
			((t_cmds *)cmd->content)->full_cmd, data->env) == -1)
		return ;
}
