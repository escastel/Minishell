/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:29:32 by escastel          #+#    #+#             */
/*   Updated: 2024/03/26 17:24:25 by escastel         ###   ########.fr       */
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
	t_listenv		*listenv;
	int				j;
	int				n;

	listenv = data->listenv;
	n = 1;
	while (n < ft_strrlen(data->env))
	{
		j = 0;
		while (listenv[j].name)
		{
			if (listenv[j].index == n)
			{
				printf("declare -x %s", listenv[j].name);
				if (listenv[j].value + 1)
					printf("=\"%s\"\n", listenv[j].value + 1);
				n++;
			}
			j++;
		}
	}
}

static void	order_export(t_data *data)
{
	t_listenv		*listenv;
	char			**env;
	int				i;
	int				j;
	int				n;

	listenv = data->listenv;
	env = data->env;
	j = 0;
	while (listenv[j].name)
	{
		i = 0;
		while (listenv[i].name)
		{
			if (ft_strlen(listenv[j].name) > ft_strlen(listenv[i].name))
				n = ft_strlen(listenv[j].name);
			if (ft_strlen(listenv[j].name) < ft_strlen(listenv[i].name))
				n = ft_strlen(listenv[i].name);
			if (ft_strncmp(listenv[j].name, listenv[i].name, n) > 0)
				listenv[j].index += 1;
			i++;
		}
		j++;
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
