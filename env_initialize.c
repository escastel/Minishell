/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_initialize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:09:52 by escastel          #+#    #+#             */
/*   Updated: 2024/04/03 12:54:37 by escastel         ###   ########.fr       */
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

static	int	listenv_initialize(t_data *data, char **new_env)
{
	int	i;

	i = 0;
	if (data->listenv)
	{
		ft_lstclear(&data->listenv, del_listenv);
		free(data->listenv);
	}
	i = 0;
	while (new_env[i])
		i++;
	data->listenv = (t_list *)malloc(sizeof(t_list) * i + 1);
	if (!data->listenv)
		return (1);
	return (0);
}

static int	fill_listenv(t_list *list, char **env)
{
	t_listenv	*listenv;
	t_list		*new;
	size_t		j;
	size_t		n;
	int			i;

	i = 0;
	while (env[i])
	{
		j = 0;
		n = ft_strlen(env[i]);
		while (env[i][j] != '=')
			j++;
		listenv = (t_listenv *)malloc(sizeof(t_listenv));
		if (!listenv)
			return (1);
		listenv->name = ft_substr(env[i], 0, j);
		listenv->value = ft_substr(env[i], j, n - j);
		listenv->index = 1;
		new = ft_lstnew(&listenv);
		ft_lstadd_back(&list, new);
		i++;
	}
	return (0);
}

int	env_initialize(t_data *data, char **new_env)
{
	if (fill_env(data, new_env))
		return (1);
	if (listenv_initialize(data, new_env))
		return (1);
	if (fill_listenv(data->listenv, data->env))
		return (1);
	return (0);
}
