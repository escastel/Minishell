/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_initialize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:09:52 by escastel          #+#    #+#             */
/*   Updated: 2024/04/05 13:19:32 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_listenv(void *content)
{
	t_listenv	*cont;

	cont = (t_listenv *)content;
	free(cont->name);
	if (cont->value)
		free(cont->value);
}

static int	fill_env(t_data *data, char **new_env)
{
	int		i;

	if (data->env)
	{
		i = 0;
		while (data->env[i])
		{
			free(data->env[i]);
			i++;
		}
		free(data->env);
	}
	data->env = (char **)malloc(sizeof(char *) * ft_strrlen(new_env) + 1);
	if (!data->env)
		return (1);
	i = 0;
	while (new_env[i])
	{
		data->env[i] = ft_strdup(new_env[i]);
		i++;
	}
	data->env[i] = NULL;
	return (0);
}

static void	update_var(t_data *data, t_listenv *list, char *env)
{
	if (!ft_strcmp(env, "OLDPWD", 6))
	{
		if (data->oldpwd)
		{
			list->value = ft_strdup(data->oldpwd);
		}
		if(!data->oldpwd)
			list->value = NULL;
	}
	if (!ft_strcmp(env, "PWD", 3))
		list->value = ft_strdup(data->pwd);
}

static int	fill_listenv(t_data *data, char **env)
{
	t_listenv	*listenv;
	t_list		*new;
	size_t		j;
	int			i;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		listenv = (t_listenv *)malloc(sizeof(t_listenv));
		if (!listenv)
			return (1);
		if (!ft_strcmp(env[i], "PWD", 3) || !ft_strcmp(env[i], "OLDPWD", 6))
			update_var(data, listenv, env[i]);
		else
			listenv->value = ft_substr(env[i], j, ft_strlen(env[i]) - j);
		listenv->name = ft_substr(env[i], 0, j);
		listenv->index = 1;
		new = ft_lstnew(listenv);
		ft_lstadd_back(&data->listenv, new);
	}
	return (0);
}

int	env_initialize(t_data *data, char **new_env)
{
	if (fill_env(data, new_env))
		return (1);
	if (fill_listenv(data, data->env))
		return (1);
	return (0);
}
