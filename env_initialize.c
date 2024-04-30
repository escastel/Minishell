/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_initialize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:09:52 by escastel          #+#    #+#             */
/*   Updated: 2024/04/30 16:29:46 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	clean_new_env(char **new_env)
{
	int	i;

	i = 0;
	while (new_env[i])
	{
		new_env[i] = NULL;
		i++;
	}
	new_env = NULL;
} */

/* static void	clear_listenv(t_listenv *list)
{
	if (list->name)
		free(list->name);
	list->name = NULL;
	if (list->value)
	{
		free(list->value);
		list->value = NULL;
	}
	free (list);
	list = NULL;
} */

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
	while (new_env[i] && ft_strncmp(new_env[i], "", ft_strlen(new_env[i])))
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
		list->name = ft_strdup("OLDPWD");
		if (data->oldpwd)
			list->value = ft_strdup(data->oldpwd);
		if (!data->oldpwd)
			list->value = NULL;
	}
	if (!ft_strcmp(env, "PWD", 3))
	{
		list->name = ft_strdup("PWD");
		if (data->pwd)
			list->value = ft_strdup(data->pwd);
		if (!data->pwd)
			list->value = NULL;
	}
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
		while (env[i][j] != '=' && env[i][j])
			j++;
		listenv = (t_listenv *)malloc(sizeof(t_listenv));
		if (!ft_strcmp(env[i], "PWD", j) || !ft_strcmp(env[i], "OLDPWD", j))
			update_var(data, listenv, env[i]);
		else
			listenv->value = ft_substr(env[i], j, ft_strlen(env[i]) - j);
		if (!listenv->name)
			listenv->name = ft_substr(env[i], 0, j);
		listenv->index = 1;
		new = ft_lstnew(listenv);
		ft_lstadd_back(&data->listenv, new);
	}
	/* clear_listenv(listenv); */
	return (0);
}

int	env_initialize(t_data *data, char **new_env)
{
 	/* t_list *aux; */
	/* int		i; */

	if (fill_env(data, new_env))
		return (1);
	if (fill_listenv(data, data->env))
			return (1);
/* 	i = -1;
	while (data->env[++i])
		printf("%s\n", data->env[i]); */
/*  	aux = data->listenv;
	while (aux)
	{
		printf("%s\n", ((t_listenv *)aux->content)->name);
		aux = aux->next;
	} */
	return (0);
}
