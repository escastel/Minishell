/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:56:36 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/03/28 12:45:23 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_command_filter(t_data *data)
{
	int		i;
	char	*cmd_slash;
	char	*tmp;

	i = 0;
	cmd_slash = ft_strjoin("/", data->cmd[0]->full_cmd[0]);
	while (data->cmd[0]->cmd_path[i])
	{
		tmp = ft_strjoin(data->cmd[0]->cmd_path[i], cmd_slash);
		data->cmd[0]->exc_path = tmp;
		if (access(data->cmd[0]->exc_path, X_OK) == 0)
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
//	if (!envp_path)
//		ft_error();
	data->cmd[0]->cmd_path = ft_split (envp_path, ':');
}

void	parser(t_data *data)
{
	int		i;
	pid_t	pid;
//	int	pipe[2];

	i = 0;
	while (data->cmd[i])
	{
		pid = fork();
//		if (p->pid == -1)
//			ft_error();
		if (pid == 0)
		{
			builtins_control(data, data->cmd[i]->full_cmd);
			ft_path(data);
			if (ft_command_filter(data) == 1)
				printf("%s\n", "COMANDO NO EJECUTABLE");
			else
				printf("%s\n", "COMANDO SI EJECUTABLE");
			execve(data->cmd[i]->exc_path, data->cmd[i]->full_cmd, data->env);
		}
		waitpid(pid, NULL, 0);
		if (pid > 0)
		{
			waitpid(pid, NULL, 0);
			i += 1;
			printf("%s\n", "PARENT");
		}
	}
}
