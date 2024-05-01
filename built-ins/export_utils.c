/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:31:27 by escastel          #+#    #+#             */
/*   Updated: 2024/05/01 12:59:12 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	data->i = ft_strrlen(data->env);
	clean_str(data);
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

void	replace_var(t_data *data, char *str)
{
	t_list		*list;
	t_list		*aux;
	char		**new_env;

	aux = NULL;
	data->i = -1;
	list = data->listenv;
	new_env = ft_calloc(ft_strrlen(data->env) + 1, sizeof(char *));
	while (data->env[++data->i] && list)
	{
		if (!ft_strncmp(((t_listenv *)list->content)->name,
				str, ft_strlen(((t_listenv *)list->content)->name)))
		{
			cpy_env(data, &new_env, str);
			if (aux)
				aux->next = list->next;
			else
				data->listenv = list->next;
			ft_lstdelone(list, del_listenv);
			break ;
		}
		aux = list;
		list = list->next;
		new_env[data->i] = ft_strdup(data->env[data->i]);
	}
}

void	add_var_env(t_data *data, char *str)
{
	char	**new_env;

	data->i = ft_strrlen(data->env);
	new_env = ft_calloc(data->i + 2, sizeof(char *));
	data->i = -1;
	while (data->env[++data->i])
		new_env[data->i] = ft_strdup(data->env[data->i]);
	new_env[data->i] = ft_strdup(str);
	data->i++;
	new_env[data->i] = NULL;
	data->i = ft_strrlen(data->env);
	clean_str(data);
	data->env = ft_calloc(data->i + 2, sizeof(char *));
	data->i = -1;
	while (new_env[++data->i])
	{
		data->env[data->i] = ft_strdup(new_env[data->i]);
		free (new_env[data->i]);
	}
	data->env[data->i] = NULL;
	free (new_env);
}
