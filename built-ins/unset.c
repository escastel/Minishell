/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:33:48 by escastel          #+#    #+#             */
/*   Updated: 2024/05/01 18:10:20 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_var(t_data *data, char *str)
{
	t_listenv	*new;
	t_list		*list;
	int			len;

	data->i = -1;
	list = data->listenv;
	while (data->env[++data->i])
	{
		new = (t_listenv *)list->content;
		len = ft_strlen(new->name);
		if (!ft_strncmp(data->env[data->i], str, len))
			return (1);
		list = list->next;
	}
	return (0);
}

static void	cpy_env(t_data *data, char ***new_env, char *str)
{
	char	**aux;

	aux = *new_env;
	while (data->env[data->i + 1])
	{
		aux[data->i] = ft_strdup(data->env[data->i + 1]);
		data->i++;
	}
	aux[data->i] = ft_strdup(str);
	aux[++data->i] = NULL;
	clean_str(data);
	data->i = ft_strrlen(data->env);
	data->env = ft_calloc(data->i + 1, sizeof(char *));
	data->i = -1;
	while (aux[++data->i])
	{
		data->env[data->i] = ft_strdup(aux[data->i]);
		free (aux[data->i]);
	}
	data->env[data->i] = NULL;
	free (aux);
}

static void	unset_util(t_data *data, char *str)
{
	char		**new_env;
	t_list		*list;
	t_list		*aux;
	t_listenv	*new;

	aux = NULL;
	list = data->listenv;
	new_env = ft_calloc(ft_strrlen(data->env) + 1, sizeof(char *));
	while (data->env[++data->i] && list)
	{
		new = (t_listenv *)list->content;
		if (!ft_strncmp(new->name, str, ft_strlen(new->name)))
		{
			cpy_env(data, &new_env, str);
			if (aux && list->next)
				aux->next = list->next;
			if (aux && !list->next)
				aux->next = NULL;
			else
				data->listenv = list->next;
			ft_lstdelone(list, del_listenv);
			break ;
		}
		aux = list;
		list = list->next;
		new_env[data->j++] = ft_strdup(data->env[data->i]);
	}
}

void	unset_built(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (check_var(data, cmd[i]))
		{
			data->i = -1;
			data->j = 0;
			unset_util(data, cmd[i]);
		}
		i++;
	}
}
