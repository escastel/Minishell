/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:49:06 by escastel          #+#    #+#             */
/*   Updated: 2024/03/21 16:52:17 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	listenv_initialize(t_data *data, char **old_env)
{
	int	i;
	int	n;
	int	flag;

	i = 0;
	flag = 1;
	while (old_env[i])
	{
		n = ft_strlen(old_env[i]);
		if (!ft_strncmp(old_env[i], "OLDPWD", n))
			flag = 0;
		i++;
	}
	if (data->listenv)
		free (data->listenv);
	if (!data->listenv)
	{
		data->listenv = (t_listenv *)malloc(sizeof(t_listenv) * i + flag + 1);
		if (!data->listenv)
			return (1);
	}
	if (flag)
		return (2);
	return (0);
}

static void	fill_listenv(t_data *data, t_listenv *listenv, char **env, int flag)
{
	int		i;
	size_t	j;
	size_t	n;

	i = 0;
	while (env[i])
	{
		j = 0;
		n = ft_strlen(env[i]);
		while (env[i][j] != '=')
			j++;
		listenv[i].name = ft_substr(env[i], 0, j);
		listenv[i].value = ft_substr(env[i], j, n - j);
		listenv[i].index = 1;
		i++;
	}
	if (flag)
	{
		n = ft_strlen("OLDPWD");
		listenv[i].name = ft_substr("OLDPWD", 0, n);
		listenv[i].index = 1;
		i++;
	}
	env[i] = NULL;
	data->env = env;
}

int	env_initialize(t_data *data, char **old_env)
{
	int				i;
	size_t			j;
	size_t			n;

	data->env = old_env;
	if (listenv_control(data, old_env) == 1)
		return (1);
	if (listenv_control(data, old_env) == 2)
		fill_listenv(data, data->listenv, data->env, 1);
	else if (!listenv_control(data, old_env))
		fill_listenv(data, data->listenv, data->env, 0);
	return (0);
}

int	init_struct(t_data *data, char **env)
{
	data->env = (char **)malloc(sizeof(char *));
	if (!data->env)
		return (1);
	if (env_initialize(data, env))
		return (1);
	data->cmd = (t_cmds **)malloc(sizeof(t_cmds *));
	if (!data->cmd)
		return (1);
	return (0);
}
