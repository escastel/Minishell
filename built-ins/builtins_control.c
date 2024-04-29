/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:02:19 by escastel          #+#    #+#             */
/*   Updated: 2024/04/29 12:41:56 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	builtins_util(t_data *data, char **full_cmd, int flag, int n)
{
	if (ft_strncmp(full_cmd[0], "exit", n) == 0)
	{
		data->builtin = 1;
		if (!flag)
			exit_built(data);
		return (true);
	}
	if (ft_strncmp(full_cmd[0], "export", n) == 0)
	{
		if (!flag)
			export_built(data, full_cmd + 1);
		return (true);
	}
	if (ft_strncmp(full_cmd[0], "pwd", n) == 0)
	{
		if (!flag)
			pwd_built();
		return (true);
	}
	if (ft_strncmp(full_cmd[0], "unset", n) == 0)
	{
		if (!flag)
			unset_built(data, full_cmd + 1);
		return (true);
	}
	return (false);
}

bool	builtins_control(t_data *data, char **full_cmd, int flag)
{
	int	n;

	n = ft_strlen(full_cmd[0]);
	if (ft_strncmp(full_cmd[0], "cd", n) == 0)
	{
		if (!flag)
			cd_built(data, full_cmd + 1);
		return (true);
	}
	if (ft_strncmp(full_cmd[0], "echo", n) == 0)
	{
		if (!flag)
			echo_built(full_cmd + 1);
		return (true);
	}
	if (ft_strncmp(full_cmd[0], "env", n) == 0)
	{
		if (!flag)
			env_built(data, full_cmd + 1);
		return (true);
	}
	return (builtins_util(data, full_cmd, flag, n));
}
