/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:31:27 by escastel          #+#    #+#             */
/*   Updated: 2024/05/06 19:40:34 by escastel         ###   ########.fr       */
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

void	add_var_list(t_data *data, char *str)
{
	t_listenv	*new;
	t_list		*list;
	int			i;

	i = 0;
	new = (t_listenv *)malloc(sizeof(t_listenv));
	while (str[i] != '=' && str[i])
		i++;
	new ->name = ft_substr(str, 0, i);
	new->value = ft_substr(str, i, ft_strlen(str) - i);
	new->index = 1;
	list = ft_lstnew(new);
	ft_lstadd_back(&data->listenv, list);
}

int	check_new_var(t_data *data, char *str, int *flag)
{
	t_listenv	*new;
	t_list		*list;
	int			len;

	data->i = -1;
	list = data->listenv;
	while (data->env[++data->i] && list)
	{
		new = (t_listenv *)list->content;
		len = ft_strlen(new->name);
		if (!ft_strncmp(new->name, str, len + 1))
		{
			data->j = 0;
			while (str[data->j] != '=' && str[data->j])
				data->j++;
			if (str[data->j] != '=')
				return (1);
			*flag = 0;
		}
		list = list->next;
	}
	return (0);
}
