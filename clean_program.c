/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:30:44 by escastel          #+#    #+#             */
/*   Updated: 2024/04/23 17:19:42 by escastel         ###   ########.fr       */
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
	free (cmd->exc_path);
	cmd->exc_path = NULL;
}

static void	clean_util(t_data *data)
{
	ft_lstclear(&data->listenv, del_listenv);
	ft_lstclear(&data->cmd, del_cmd);
	free (data->listenv);
	free (data->cmd);
	if (data->oldpwd)
		free (data->oldpwd);
	if (data->pwd)
	{
		free (data->pwd);
		data->pwd = NULL;
	}
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
	free (data->cmd_path);
	clean_util(data);
}
