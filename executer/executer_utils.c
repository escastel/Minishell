/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:32:28 by escastel          #+#    #+#             */
/*   Updated: 2024/05/06 14:48:28 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_command_filter_2(t_data *data, t_list *cmd, char **cmd_slash, char **tmp)
{
	int	i;

	i = 0;
	if (((t_cmds *)cmd->content)->exc_path)
		free (((t_cmds *)cmd->content)->exc_path);
	while (data->cmd_path && data->cmd_path[i])
	{
		*tmp = ft_strjoin(data->cmd_path[i], *cmd_slash);
		((t_cmds *)cmd->content)->exc_path = *tmp;
		if (access(((t_cmds *)cmd->content)->exc_path, X_OK) == 0)
		{
			free(*cmd_slash);
			return (0);
		}
		((t_cmds *)cmd->content)->exc_path = NULL;
		free(*tmp);
		i += 1;
	}
	return (1);
}

int	ft_command_filter(t_data *data, t_list *cmd)
{
	char	*cmd_slash;
	char	*tmp;

	if (ft_strlen(((t_cmds *)cmd->content)->full_cmd[0]) == 0)
		return (1);
	cmd_slash = ft_strjoin("/", ((t_cmds *)cmd->content)->full_cmd[0]);
	if (ft_command_filter_2(data, cmd, &cmd_slash, &tmp) == 0)
	{
		return (0);
	}
	if (access(((t_cmds *)cmd->content)->full_cmd[0], X_OK) == 0)
	{
		((t_cmds *)cmd->content)
			->exc_path = ft_strdup(((t_cmds *)cmd->content)->full_cmd[0]);
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
		return (1);
	data->cmd_path = ft_split (envp_path, ':');
	return (0);
}

void	ft_file_or_directory(t_data *data, t_list *cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (builtins_control(data, ((t_cmds *)cmd->content)->full_cmd, 1) == 0)
	{
		if (ft_command_filter(data, cmd) == 0)
		{
			if (((t_cmds *)cmd->content)->full_cmd[1])
			{
				while (((t_cmds *)cmd->content)->full_cmd[i])
				{
					flag = open(((t_cmds *)cmd->content)->full_cmd[i], O_EXCL);
					if (flag == -1)
						data->status = 1;
					i += 1;
				}
			}
		}
	}
}

void	ft_no_cmd(t_data *data, char **full_cmd)
{
	dup2(data->fdout, STDOUT_FILENO);
	printf(RED);
	printf("%s: command not found\n", full_cmd[0]);
	printf(RESET);
	data->status = 127;
	return ;
}
