/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:24:36 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/05/06 19:07:54 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_execute(t_data *data, t_list	*cmd, int flag)
{
	pid_t	pid;

	ft_path(data);
	pipe(data->pipe);
	pid = fork();
	if (pid == -1)
		exit (EXIT_FAILURE);
	if (pid == 0)
	{
		ft_child(data, cmd, flag);
	}
	else
	{
		waitpid(pid, NULL, WUNTRACED);
		ft_parent(data, cmd);
	}
	return (0);
}

static int	ft_execute_one(t_data *data, t_list *cmd)
{
	pid_t	pid;

	ft_child_redir(data, cmd);
	if ((builtins_control(data,
				((t_cmds *)data->cmd->content)->full_cmd, 0)) == 1)
		return (0);
	ft_path(data);
	if (ft_command_filter(data, cmd) == 0)
	{
		pid = fork();
		if (pid == -1)
			exit (EXIT_FAILURE);
		if (pid == 0)
			ft_xone_child(data, cmd);
		else
		{
			waitpid(pid, NULL, 0);
			ft_parent(data, cmd);
		}
	}
	else
		ft_no_cmd(data, ((t_cmds *)cmd->content)->full_cmd);
	return (data->status);
}

static int	ft_execute_pipe(t_data *data, t_list *cmd)
{
	if (builtins_control(data, ((t_cmds *)cmd->content)->full_cmd, 1) == 0)
		ft_execute(data, cmd, 1);
	else if (builtins_control(data, ((t_cmds *)cmd->content)->full_cmd, 1) == 1)
		ft_execute(data, cmd, 0);
	return (data->status);
}

void	executer(t_data *data)
{
	t_list	*aux;

	if (!((t_cmds *)data->cmd->content)->full_cmd[0]) //este es el parche, creo que funciona
		return ;
	data->fdin = dup(STDIN_FILENO);
	data->fdout = dup(STDOUT_FILENO);
	aux = data->cmd;
	signal(SIGQUIT, handler);
	g_signal = 0;
	if (aux->next == NULL)
		data->status = ft_execute_one(data, aux);
	else
	{
		while (aux)
		{
			data->status = ft_execute_pipe(data, aux);
			ft_clean_path(data);
			aux = aux->next;
		}
	}
	dup2(data->fdin, STDIN_FILENO);
	dup2(data->fdout, STDOUT_FILENO);
	return ;
}
