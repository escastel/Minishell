/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:24:36 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/05/01 17:19:01 by escastel         ###   ########.fr       */
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
		((t_cmds *)cmd->content)->exc_path = NULL;
		free(tmp);
		i += 1;
	}
	if (access(((t_cmds *)cmd->content)->full_cmd[0], X_OK) == 0)
	{
		((t_cmds *)cmd->content)->exc_path = ft_strdup(((t_cmds *)cmd->content)->full_cmd[0]);
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

void	ft_no_cmd(t_data *data, char **full_cmd)
{
	dup2(data->fd, STDOUT_FILENO);
	printf("%s: command not found\n", full_cmd[0]);
	data->status = 127;
	return ;
}

void	ft_child(t_data *data, t_list *cmd, int flag)
{
	ft_child_redir(data, cmd);
	if (flag == 1)
	{
		if (ft_command_filter(data, cmd) == 0)
		{
			if (execve(((t_cmds *)cmd->content)->exc_path,
					((t_cmds *)cmd->content)->full_cmd, data->env) == -1)
				exit (EXIT_FAILURE); //ft error o exit failure?
		}
	}
	else if (flag == 0)
	{
		builtins_control(data, ((t_cmds *)cmd->content)->full_cmd, 0);
		exit(0);
	}
	ft_no_cmd(data, ((t_cmds *)cmd->content)->full_cmd);
	exit(0);
}

int	ft_execute(t_data *data, t_list	*cmd, int flag)
{
	pid_t	pid;

	pipe(data->pipe);
	pid = fork();
	if (pid == -1)
		exit (EXIT_FAILURE);//	ft_error();
	if (pid == 0)
	{
		ft_child(data, cmd, flag);
	}
	else
	{
		waitpid(pid, NULL, 0);
		ft_parent(data, cmd);
	}
	return (0);
}

int	ft_execute_one(t_data *data, t_list *cmd)
{
	pid_t	pid;

	if ((builtins_control(data,
				((t_cmds *)data->cmd->content)->full_cmd, 0)) == 1)
		return (0);
	else if (ft_command_filter(data, cmd) == 0)
	{
		pid = fork();
		if (pid == -1)
			exit (EXIT_FAILURE);//	ft_error();
		if (pid == 0)
		{
			ft_child_redir(data, cmd);
			if (execve(((t_cmds *)cmd->content)->exc_path,
					((t_cmds *)cmd->content)->full_cmd, data->env) == -1)
				return (1); //ft error o exit failure?
		}
		else
			waitpid(pid, NULL, 0);
	}
	else
		ft_no_cmd(data, ((t_cmds *)cmd->content)->full_cmd);
	return (0);
}

void	ft_execute_pipe(t_data *data, t_list *cmd)
{
	if (builtins_control(data, ((t_cmds *)cmd->content)->full_cmd, 1) == 0)
		ft_execute(data, cmd, 1);
	else if (builtins_control(data, ((t_cmds *)cmd->content)->full_cmd, 1) == 1)
		ft_execute(data, cmd, 0);
}

void	executer(t_data *data)
{
	t_list	*aux;
	int		fd;

	fd = dup(STDIN_FILENO);
	data->fd = dup(STDIN_FILENO);
	aux = data->cmd;
	signal(SIGQUIT, handler);
	g_signal = 0;
	if (aux->next == NULL)
	{
		ft_execute_one(data, aux);
	}
	else
	{
		while (aux)
		{
			ft_execute_pipe(data, aux);
			aux = aux->next;
		}
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return ;
	return ;
}



/* #include "minishell.h"

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
		printf("CO:O\n");
		if ((builtins_control(data, ((t_cmds *)data->cmd->content)->full_cmd, 0)) == 1)
			exit (EXIT_SUCCESS); //liberaciones?
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
		dup2((((t_cmds *)cmd->content)->outfile), STDOUT_FILENO);
		printf ("OUT: %d\n", ((t_cmds *)cmd->content)->outfile);
		if ((builtins_control(data, ((t_cmds *)data->cmd->content)->full_cmd, 0)) == 1)
			exit (EXIT_SUCCESS); //liberaciones?
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

void	executer(t_data *data)
{
	t_list	*aux;
	int		fd;

	fd = dup(STDIN_FILENO);
	aux = data->cmd;
	while (aux->next)
	{
		if (ft_command_filter(data, aux) == 0)
		{
			if (pipe(data->pipe) == -1)
				return ;
			if (ft_execute(data, aux) == 1)
				return ;
		}
		else
			printf("No hay comando jfa\n");
		aux = aux->next;
	}
	if (ft_command_filter(data, aux) == 0)
		if (ft_execute_last(data, aux))
			return ;
	if (dup2(fd, STDIN_FILENO) == -1)
		return ;
	return ;
} */