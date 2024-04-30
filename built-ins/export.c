/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:29:32 by escastel          #+#    #+#             */
/*   Updated: 2024/04/30 16:21:44 by escastel         ###   ########.fr       */
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
	int				len;

	index = 1;
	len = ft_strrlen(data->env);
	while (index < len)
	{
		aux = data->listenv;
		while (aux)
		{
			listenv = ((t_listenv *)aux->content);
			if (listenv->index == index)
			{
				printf("declare -x %s", listenv->name);
				if (listenv->value)
					printf("=\"%s\"\n", listenv->value + 1);
				else
					printf("\n");
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
	t_listenv		*listenv_aux;
	t_listenv		*listenv_tmp;
	int				index;

	aux = data->listenv;
	while (aux->next)
	{
		listenv_aux = ((t_listenv *)aux->content);
		tmp = data->listenv;
		while (tmp->next && listenv_aux->name)
		{
			listenv_tmp = ((t_listenv *)tmp->content);
			if (ft_strlen(listenv_aux->name) > ft_strlen(listenv_tmp->name))
				index = ft_strlen(listenv_aux->name);
			if (ft_strlen(listenv_aux->name) < ft_strlen(listenv_tmp->name))
				index = ft_strlen(listenv_tmp->name);
			if (ft_strncmp(listenv_aux->name, listenv_tmp->name, index) > 0)
				listenv_aux->index += 1;
			tmp = tmp->next;
		}
		aux = aux->next;
	}
}

static void	export_var(t_data *data, char *str)
{
	int	flag;
/* 	t_list	*list; */

	flag = 0;
	check_new_var(data, str, &flag);
	add_var_env(data, str, &flag);
/* 	list = data->listenv;
	while (list)
	{
		printf("%s%s\n", ((t_listenv *)list->content)->name, ((t_listenv *)list->content)->value);
		list = list->next;
	} */
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
