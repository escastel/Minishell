/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:29:32 by escastel          #+#    #+#             */
/*   Updated: 2024/05/06 18:37:11 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	export_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[0] >= '0' && str[0] <= '9') || (!ft_isalnum(str[i])
				&& str[i] != '/' && str[i] != '_' && str[i] != '='))
		{
			printf(RED);
			printf("michishell: export: `%s': not a valid identifier\n", str);
			printf(RESET);
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

	data->i = 1;
	while (data->i < ft_strrlen(data->env))
	{
		aux = data->listenv;
		while (aux)
		{
			listenv = ((t_listenv *)aux->content);
			if (listenv->index == data->i)
			{
				printf("declare -x %s", listenv->name);
				if (listenv->value)
					printf("=\"%s\"\n", listenv->value + 1);
				else
					printf("\n");
				data->i++;
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
	while (aux)
	{
		listenv_aux = ((t_listenv *)aux->content);
		tmp = data->listenv;
		while (tmp)
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
	int		flag;

	flag = 1;
	if (check_new_var(data, str, &flag))
		return ;
	if (flag)
		add_var_env(data, str);
	if (!flag)
		replace_var(data, str);
	add_var_list(data, str);
}

void	export_built(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	if (!cmd[0])
	{
		reset_index(data);
		order_export(data);
		export_print(data);
	}
	else
	{
		while (cmd[i])
		{
			data->status = export_error(cmd[i]);
			if (!data->status)
				export_var(data, cmd[i]);
			i++;
		}
	}
}
