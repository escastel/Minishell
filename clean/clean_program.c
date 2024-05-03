/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:30:44 by escastel          #+#    #+#             */
/*   Updated: 2024/05/03 18:37:50 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_listenv(void *content)
{
	t_listenv	*cont;

	cont = (t_listenv *)content;
	if (cont->name)
		free (cont->name);
	if (cont->value)
		free (cont->value);
	cont->value = NULL;
	if (cont)
		free (cont);
}

void	del_cmd(void	*content)
{
	t_cmds	*cmd;
	int		i;

	cmd = (t_cmds *)content;
	i = 0;
	if (cmd->full_cmd)
	{
		while (cmd->full_cmd[i])
		{
			free (cmd->full_cmd[i]);
			i++;
		}
		free (cmd->full_cmd);
	}
	if (cmd->exc_path)
		free (cmd->exc_path);
	if (cmd)
		free (cmd);
}

static void	clean_util(t_data *data)
{
	if (data->listenv)
	{
		ft_lstclear(&data->listenv, del_listenv);
		free (data->listenv);
	}
	if (data->cmd)
	{
		ft_lstclear(&data->cmd, del_cmd);
		free (data->cmd);
	}
	if (data->oldpwd)
		free (data->oldpwd);
	if (data->pwd)
		free (data->pwd);
	if (data)
		free (data);
}

void	clean_program(t_data *data)
{
	int	i;

	i = 0;
	if (data->env)
	{
		while (data->env[i])
		{
			free (data->env[i]);
			i++;
		}
		free (data->env);
	}
	clean_util(data);
}
