/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:56:23 by escastel          #+#    #+#             */
/*   Updated: 2024/03/19 17:21:18 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	listenv_control(t_data *data, char **old_env)
{
	int	i;

	i = 0;
	while (old_env[i])
		i++;
	if (data->listenv)
		free (data->listenv);
	if (!data->listenv)
		data->listenv = (t_listenv *)malloc(sizeof(t_listenv) * i + 1);
}

void	env_initialize(t_data *data, char **old_env)
{
	t_listenv		*listenv;
	char			**env;
	int				i;
	size_t			j;
	size_t			n;

	if (!data->env)
		data->env = (char **)malloc(sizeof(char *));
	listenv_control(data, old_env);
	data->env = old_env;
	env = data->env;
	listenv = data->listenv;
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
	data->env[i] = NULL;
}

static void	env_print(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (data->listenv[i].value)
			printf("%s\n", data->env[i]);
		i++;
	}
}

void	env_built(t_data *data, char **cmd)
{
	int	flag;

	flag = open(cmd[0], O_DIRECTORY);
	if (flag != -1)
	{
		printf("env: %s: Permission denied\n", cmd[0]);
		return ;
	}
	if (cmd[0])
	{
		printf("env: %s: No such file or directory\n", cmd[0]);
		return ;
	}
	env_print(data);
}
