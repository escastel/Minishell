/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:56:36 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/04/10 10:47:45 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_command_filter(t_data *data)
{
	int		i;
	char	*cmd_slash;
	char	*tmp;

	i = 0;
	cmd_slash = ft_strjoin("/", ((t_cmds *)data->cmd->content)->full_cmd[0]);
	while (data->cmd_path[i])
	{
		tmp = ft_strjoin(data->cmd_path[i], cmd_slash);
		((t_cmds *)data->cmd->content)->exc_path = tmp;
		if (access(((t_cmds *)data->cmd->content)->exc_path, X_OK) == 0)
			return (0);
		free(tmp);
		i += 1;
	}
	return (1);
}

void	ft_path(t_data *data)
{
	char	*envp_path;
	int		i;

	i = 0;
	envp_path = 0;
	while (data->env[i])
	{
		if (strncmp(data->env[i], "PATH=", 5) == 0)
		{
			envp_path = data->env[i] + 5;
			break ;
		}
		i++;
	}
	if (!envp_path)
		exit (EXIT_FAILURE); //ft_error();
	data->cmd_path = ft_split (envp_path, ':');
}

void	ft_execute(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit (EXIT_FAILURE);//	ft_error();
	if (pid == 0)
	{
		close(data->pipe[0]);
		dup2(data->pipe[1], STDOUT_FILENO);
		if (execve(((t_cmds *)data->cmd->content)->exc_path, ((t_cmds *)data->cmd->content)->full_cmd, data->env) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(data->pipe[1]);
		dup2(data->pipe[0], STDIN_FILENO); // la comprbasion de errore
	}
}

void	ft_execute_last(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit (EXIT_FAILURE);//	ft_error();
	if (pid == 0)
	{
		close (data->pipe[0]);
		dup2(((t_cmds *)data->cmd->content)->outfile, STDOUT_FILENO);
		if (execve(((t_cmds *)data->cmd->content)->exc_path, ((t_cmds *)data->cmd->content)->full_cmd, data->env) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

void	parser(t_data *data)
{
	int		i;

	i = 0;
	ft_path(data);
	while (data->cmd->next)
	{
		pipe(data->pipe);
	//LAS REDIRECCIONES ESTAN DENTRO DEL EXECUTE NO AFECTA AL BUILTIN, SE PODRIAN sacar? o meter el builtin dentro con boolean
		builtins_control(data, ((t_cmds *)data->cmd->content)->full_cmd); //boolean?
		if (ft_command_filter(data) == 0)
		{
			ft_execute(data);
		}
		data->cmd = data->cmd->next;
	}
	builtins_control(data, ((t_cmds *)data->cmd->content)->full_cmd);
	if (ft_command_filter(data) == 0)
		ft_execute_last(data);
	dup2(((t_cmds *)data->cmd->content)->infile, STDIN_FILENO);
}
