/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:29:32 by escastel          #+#    #+#             */
/*   Updated: 2024/04/03 12:44:49 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	export_error(char *str)
{
	int	flag;
	int	i;

	flag = open(str, O_DIRECTORY);
	if (flag == 3)
	{
		printf("michishell: export: `%s': not a valid identifier\n", str);
		return (flag);
	}
	i = 0;
	while (str[i])
	{
		if ((str[0] >= '0' && str[0] <= '9') || str[i] == '.')
		{
			printf("michishell: export: `%s': not a valid identifier\n", str);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	export_print(t_data *data)
{
	t_list			*aux;
	t_listenv		*listenv;
	int				index;

	index = 1;
	while (index < ft_strrlen(data->env))
	{
		aux = data->listenv;
		while (aux)
		{
			listenv = ((t_listenv *)aux->content);
			if (listenv->index == index)
			{
				printf("declare -x %s", listenv->name);
				if (listenv->value + 1)
					printf("=\"%s\"\n", listenv->value + 1);
				index++;
			}
			aux = aux->next;
		}
	}
}

static void	order_export(t_data *data)
{
	t_list			*aux;
	t_list			*tmp;
	t_listenv		*listenv;
	t_listenv		*listenv_next;
	int				index;

	aux = data->listenv;
	while (aux)
	{
		listenv = ((t_listenv *)aux->content);
		tmp = data->listenv;
		while (tmp)
		{
			listenv_next = ((t_listenv *)tmp->content);
			if (ft_strlen(listenv->name) > ft_strlen(listenv_next->name))
				index = ft_strlen(listenv->name);
			if (ft_strlen(listenv->name) < ft_strlen(listenv_next->name))
				index = ft_strlen(listenv_next->name);
			if (ft_strncmp(listenv->name, listenv_next->name, index) > 0)
				listenv->index += 1;
			tmp = tmp->next;
		}
		aux = aux->next;
	}
}

void	export_var(t_data *data, char *str)
{
	char		**env;
	int			j;

	env = data->env;
	j = 0;
	while (env[j] != NULL)
		j++;
	env[j] = str;
	j++;
	env[j] = NULL;
	env_initialize(data, env);
}

void	export_built(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	if (!cmd[0])
	{
		order_export(data);
		export_print(data);
	}
	else
	{
		while (cmd[i])
		{
			if (!export_error(cmd[i]))
				export_var(data, cmd[i]);
			i++;
		}
	}
}
