/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:29:32 by escastel          #+#    #+#             */
/*   Updated: 2024/03/18 20:10:54 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	export_var(t_data *data, char **str)
{
	char		**env;
	int			i;
	int			j;

	env = data->env;
	j = 0;
	while (env[j] != NULL)
		j++;
	i = 0;
	while (str[i] != NULL)
	{
		env[j] = str[i];
		j++;
		i++;
	}
	env[j] = NULL;
	env_built(data, env, 1);
}

void	export_built(t_data *data, char **str)
{
	if (!str[0])
	{
		order_export(data);
		export_print(data);
	}
	else
	{
		export_var(data, str);
		order_export(data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	/* int		i; */

	(void)argc;
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	env_built(data, env, 1);
	export_built(data, argv + 1);
	/* i = 0;
	while (data->env[i])
	{
		printf("%s%s\n", data->listenv[i].name, data->listenv[i].value);
		i++;
	} */
	export_print(data);
}
