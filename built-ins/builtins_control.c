/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:02:19 by escastel          #+#    #+#             */
/*   Updated: 2024/05/06 13:08:08 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	builtins_util(t_data *data, char **full_cmd, int flag)
{
	if (ft_strncmp(full_cmd[0], "exit", ft_strlen("exit") + 1) == 0)
	{
		data->builtin = 1;
		if (!flag)
			exit_built(data, full_cmd + 1);
		return (true);
	}
	if (ft_strncmp(full_cmd[0], "pwd", ft_strlen("pwd") + 1) == 0)
	{
		if (!flag)
			pwd_built();
		return (true);
	}
	if (ft_strncmp(full_cmd[0], "unset", ft_strlen("unset") + 1) == 0)
	{
		if (!flag)
			unset_built(data, full_cmd + 1);
		return (true);
	}
	return (false);
}

bool	builtins_control(t_data *data, char **full_cmd, int flag)
{
	if (ft_strncmp(full_cmd[0], "cd", ft_strlen("cd") + 1) == 0)
	{
		if (!flag)
			cd_built(data, full_cmd + 1);
		return (true);
	}
	if (ft_strncmp(full_cmd[0], "echo", ft_strlen("echo") + 1) == 0)
	{
		if (!flag)
			echo_built(full_cmd + 1);
		return (true);
	}
	if (ft_strncmp(full_cmd[0], "env", ft_strlen("env") + 1) == 0)
	{
		if (!flag)
			env_built(data, full_cmd + 1);
		return (true);
	}
	if (ft_strncmp(full_cmd[0], "export", ft_strlen("export") + 1) == 0)
	{
		if (!flag)
			export_built(data, full_cmd + 1);
		return (true);
	}
	return (builtins_util(data, full_cmd, flag));
}
