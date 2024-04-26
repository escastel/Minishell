/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:30:44 by escastel          #+#    #+#             */
/*   Updated: 2024/04/26 17:35:15 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_listenv(void *content)
{
	t_listenv	*cont;

	cont = (t_listenv *)content;
	cont->name = NULL;
	cont->value = NULL;
}

void	del_cmd(void	*content)
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
}

static void	clean_util(t_data *data)
{
	ft_lstclear(&data->listenv, del_listenv);
	ft_lstclear(&data->cmd, del_cmd);
	if (data->listenv)
		free (data->listenv);
	if (data->cmd)
		free (data->cmd);
	if (data->oldpwd)
		free (data->oldpwd);
	if (data->pwd)
		free (data->pwd);
	free (data);
}

void	clean_program(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		free (data->env[i]);
		data->env[i] = NULL;
		i++;
	}
	if (data->env)
		free (data->env);
	data->env = NULL;
	i = 0;
	if (data->cmd_path[i])
	{
		while (data->cmd_path[i])
		{
			free (data->cmd_path[i]);
			data->cmd_path[i] = NULL;
			i++;
		}
	}
	if (data->cmd_path)
		free (data->cmd_path);
	clean_util(data);
}
