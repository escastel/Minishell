/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:56:36 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/04/24 12:39:34 by lcuevas-         ###   ########.fr       */
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

int	ft_redir(t_data *data, int i)
{
	if (data->prompt[i][0] == '<')
	{
		i += 1;
		if (data->prompt[i][0] == '<')
			return (++i);
		else
		{
			((t_cmds *)data->cmd->content)->infile = open(data->prompt[i], O_RDONLY, 00444);
			return (++i);
		}
	}
	else if (data->prompt[i][0] == '>')
	{
		i += 1;
		if (data->prompt[i][0] == '>')
			return (++i);
		else
		{
			((t_cmds *)data->cmd->content)->infile = open(data->prompt[i], O_WRONLY | O_CREAT | O_TRUNC, 00644);
			return (++i);
		}
	}
	return (i);
}

void	ft_noduler(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->prompt[i])
	{
		if ((data->prompt[i][0] == '<') || (data->prompt[i][0] == '>'))
			i = ft_redir(data, i);
/* 		if (data->prompt[i][0] == '|')
		{
			ft_next_node(data);
			j = 0;
		} */
		((t_cmds *)data->cmd->content)->full_cmd[j] = data->prompt[i];
		printf("%s\n", ((t_cmds *)data->cmd->content)->full_cmd[j]);
		i += 1;
		j += 1;
	}
	return ;
}

t_cmds	*ft_new_cmd_node(void)
{
	t_cmds		*command;

	command = ft_calloc(1, ((sizeof(t_cmds))));
	command->full_cmd = ft_calloc(1, (sizeof(char **)));
	command->exc_path = ft_calloc(1, (sizeof(char *)));
	command->outfile = 1; // por probarlo de guardar el fd desde el principio
	command->infile = 0;
	return (command);
}

void	ft_new_cmd(t_data *data)
{
	t_list	*new;
	t_cmds	*command;

	command = ft_new_cmd_node();
	new = ft_lstnew(command);
	data->cmd = new;
}

int	parser(t_data *data)
{
	ft_new_cmd(data);
	ft_path(data);
	ft_noduler(data);
	return (0);
}
