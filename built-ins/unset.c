/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:33:48 by escastel          #+#    #+#             */
/*   Updated: 2024/04/30 17:34:43 by escastel         ###   ########.fr       */
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
/* 
static void	unset_util(t_data *data, char *str)
{
	char		**new_env;
	t_list		*list;
	t_listenv	*new;
	int			len;

	data->i = 0;
	data->j = 0;
	list = data->listenv;
	new_env = (char **)malloc(sizeof(char *) * ft_strrlen(data->env));
	while (data->env[data->i])
	{
		new = (t_listenv *)list->content;
		len = ft_strlen(new->name);
		if (ft_strncmp(new->name, str, len))
		{
			new_env[j] = ft_strdup(data->env[i]);
			i++;
			j++;
		}
		else if (!ft_strncmp(data->env[i], str, len))
			i++;
	}
	new_env[j] = NULL;
	env_initialize(data, new_env);
	i = 0;
	while (new_env[i])
	{
		free(new_env[i]);
		i++;
	}
	free(new_env);
} */

void	unset_built(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (check_var(data, cmd[i]))
			/* unset_util(data, cmd[i]); */
		i++;
	}
}
