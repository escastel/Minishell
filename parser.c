/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:56:36 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/04/22 17:28:26 by escastel         ###   ########.fr       */
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

int	ft_path(t_data *data)
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
		return (1); //ft_error();
	data->cmd_path = ft_split (envp_path, ':');
	return (0);
}

int	ft_execute(t_data *data, t_list	*cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit (EXIT_FAILURE);//	ft_error();
	if (pid == 0)
	{
		close(data->pipe[0]);
		if ((((t_cmds *)cmd->content)->infile) != STDIN_FILENO)
			dup2((((t_cmds *)cmd->content)->infile), STDIN_FILENO);
		if ((((t_cmds *)cmd->content)->outfile) != STDOUT_FILENO)
			dup2((((t_cmds *)cmd->content)->outfile), STDOUT_FILENO);
		else if (dup2(data->pipe[1], STDOUT_FILENO) == -1) // habria uqe hacerlo con el infile? podria igual el infile aquí dentro
			return (1);
		if (execve(((t_cmds *)cmd->content)->exc_path, ((t_cmds *)cmd->content)->full_cmd, data->env) == -1)
			return (1); //ft error o exit failure?
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(data->pipe[1]);
		if (dup2(data->pipe[0], STDIN_FILENO) == -1)
			return (1); // la comprbasion de errore
		return (0);
	}
	return (0);
}

int	ft_execute_last(t_data *data, t_list *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit (EXIT_FAILURE);//	ft_error();
	if (pid == 0)
	{
		close (data->pipe[0]);
		if ((((t_cmds *)cmd->content)->infile) != STDIN_FILENO)
			dup2((((t_cmds *)cmd->content)->infile), STDIN_FILENO);
		if (dup2(((t_cmds *)cmd->content)->outfile, STDOUT_FILENO) == -1)
			return (1);
		if (execve(((t_cmds *)cmd->content)->exc_path, ((t_cmds *)cmd->content)->full_cmd, data->env) == -1)
			return (1); //ft error o exit failure?
	}
	else
	{
		waitpid(pid, NULL, 0);
		return (0);
	}
	return (0);
}

int	parser(t_data *data)
{
	t_list	*aux;
	int		i;
	int		fd = dup(STDIN_FILENO);

	i = 0;
	if (ft_path(data)) //HAY que parchear esto para las rutas absolutas cuamdpo se ace el unset PATH
		return (1);
	aux = data->cmd;
	while (aux->next)
	{
		if (pipe(data->pipe) == -1)
			return (1);
		builtins_control(data, ((t_cmds *)data->cmd->content)->full_cmd, 1); //boolean? y meterlo en el execute
		if (ft_command_filter(data, aux) == 0)
		{
			if (ft_execute(data, aux))
				return (1);
		}
		aux = aux->next;
	}
	builtins_control(data, ((t_cmds *)data->cmd->content)->full_cmd, 0);
	if (ft_command_filter(data, aux) == 0)
		if (ft_execute_last(data, aux))
			return (1);
// quite los close de aqui, pueden volver si queremos
	if (dup2(fd, STDIN_FILENO) == -1)
		return (1);
	return (0);
}
