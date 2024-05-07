/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:29:32 by escastel          #+#    #+#             */
/*   Updated: 2024/05/07 12:07:33 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	export_error(t_data *data, char *str)
{
	char	*aux;

	data->i = -1;
	if (str[0] == '=')
		data->i++;
	while (str[++data->i] && str[data->i] != '=')
	{
		if ((str[0] >= '0' && str[0] <= '9')
			|| (!ft_isalnum(str[data->i]) && str[data->i] != '_'))
		{
			printf(RED);
			printf("michishell: export: `%s': not a valid identifier\n", str);
			return (1);
		}
	}
	aux = ft_substr(str, 0, data->i);
	if (open(aux, O_DIRECTORY) == 3 || aux[0] == '=')
	{
		printf(RED);
		printf("michishell: export: `%s': not a valid identifier\n", aux);
		return (free (aux), 1);
	}
	return (free(aux), 0);
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
			data->status = export_error(data, cmd[i]);
			if (!data->status)
				export_var(data, cmd[i]);
			i++;
		}
	}
}
