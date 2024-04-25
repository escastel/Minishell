/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:24:36 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/04/25 11:29:42 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_command_filter(t_data *data, t_list *cmd)
{
	int		i;
	char	*cmd_slash;
	char	*tmp;

	i = 0;
	cmd_slash = ft_strjoin("/", ((t_cmds *)cmd->content)->full_cmd[0]);
	while (data->cmd_path[i])
	{
		tmp = ft_strjoin(data->cmd_path[i], cmd_slash);
		((t_cmds *)cmd->content)->exc_path = tmp;
		if (access(((t_cmds *)cmd->content)->exc_path, X_OK) == 0)
		{
			free(cmd_slash);
			return (0);
		}
		free(tmp);
		i += 1;
	}
	if (access(((t_cmds *)cmd->content)->full_cmd[0], X_OK) == 0)
	{
		((t_cmds *)cmd->content)->exc_path =  ft_strdup(((t_cmds *)cmd->content)->full_cmd[0]);
		return (0);
	}
	free((cmd_slash));
	return (1);
}

void	ft_parent(t_data *data, t_list	*cmd)
{
	if (cmd->next)
	{
		close(data->pipe[1]);
		if (dup2(data->pipe[0], STDIN_FILENO) == -1)
			return ; // la comprbasion de errore
		return ;
	}
	return ;
}

void	ft_child(t_data *data, t_list	*cmd)
{
	close(data->pipe[0]);
	if ((((t_cmds *)cmd->content)->infile) != STDIN_FILENO)
		dup2((((t_cmds *)cmd->content)->infile), STDIN_FILENO);
	if (cmd->next)
	{
		if ((((t_cmds *)cmd->content)->outfile) != STDOUT_FILENO)
			dup2((((t_cmds *)cmd->content)->outfile), STDOUT_FILENO);
		else if (dup2(data->pipe[1], STDOUT_FILENO) == -1) // habria uqe hacerlo con el infile? podria igual el infile aquí dentro
			return ;
	}
	else
		dup2(((t_cmds *)cmd->content)->outfile, STDOUT_FILENO);
	if (builtins_control(data, ((t_cmds *)data->cmd->content)->full_cmd, ((t_cmds *)data->cmd->content)->builtin) == FALSE)
	{
		if (execve(((t_cmds *)cmd->content)->exc_path, ((t_cmds *)cmd->content)->full_cmd, data->env) == -1)
			return ; //ft error o exit failure?
	}
	exit(0); // y llamar a las liberaciones no?
}

int	ft_execute(t_data *data, t_list	*cmd)
{
	pid_t	pid;

	printf("intraexec\n");
	pipe(data->pipe);
	pid = fork();
	if (pid == -1)
		exit (EXIT_FAILURE);//	ft_error();
	if (pid == 0)
	{
		ft_child(data, cmd);
		return (0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		ft_parent(data, cmd);
		return (0);
	}
	return (0);
}

void	executer(t_data *data)
{
	t_list	*aux;
	int		fd;

	fd = dup(STDIN_FILENO);
	aux = data->cmd;
	while (aux)
	{
		if (ft_command_filter(data, aux) == 0)
			ft_execute(data, aux);
		aux = aux->next;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return ;
	return ;
}
