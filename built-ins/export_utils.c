/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:31:27 by escastel          #+#    #+#             */
/*   Updated: 2024/04/30 16:21:26 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (!ft_strncmp(new->name, str, len))
		{
			data->j = 0;
			while (str[data->j] != '=' && str[data->j])
				data->j++;
			if (str[data->j] != '=')
				return (1);
			*flag = 1;
		}
		list = list->next;
	}
	return (0);
}

static void	clean_str(t_data *data)
{
	data->i = -1;
	while (data->env[++data->i])
		free (data->env[data->i]);
	free (data->env);
}

static void	add_var_list(t_data *data, char *str)
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

static char	**replace_var(t_data *data, char *str, char **new_env)
{
	t_list		*list;
	t_list		*aux;

	aux = NULL;
	data->i = -1;
	list = data->listenv;
	while (new_env[++data->i] && list)
	{
		if (!ft_strncmp(((t_listenv *)list->content)->name,
			str, ft_strlen(((t_listenv *)list->content)->name)))
		{
			free (new_env[data->i]);
			new_env[data->i] = ft_strdup(str);
			if (aux)
				aux->next = list->next;
			else
				data->listenv = list->next;
			ft_lstdelone(list, del_listenv);
			add_var_list(data, str);
			break ;
		}
		aux = list;
		list = list->next;
	}
	return (new_env);
}

void	add_var_env(t_data *data, char *str, int *flag)
{
	char	**new_env;

	data->i = ft_strrlen(data->env);
	new_env = (char **)malloc(sizeof(char *) * data->i + 1 + *flag);
	data->i = -1;
	while (data->env[++data->i])
		new_env[data->i] = ft_strdup(data->env[data->i]);
	if (*flag)
		new_env = replace_var(data, str, new_env);
	if (!*flag)
	{
		new_env[data->i] = ft_strdup(str);
		add_var_list(data, str);
		data->i++;
	}
	new_env[data->i] = NULL;
	data->i = -1;
	clean_str(data);
	data->env = (char **)malloc(sizeof(char *) * ft_strrlen(new_env) + 1);
	while (new_env[++data->i])
	{
		data->env[data->i] = ft_strdup(new_env[data->i]);
		free (new_env[data->i]);
	}
	free (new_env);
}
