/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:56:23 by escastel          #+#    #+#             */
/*   Updated: 2024/03/18 19:59:52 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// PONER UN PARCHE DONDE NO PERMITA QUE ENV TENGA ALGUNA VARIABLE ?

void	env_print(t_data *data)
{
	int	i;

	i = 0;
	while (data->listenv[i].name)
	{
		if (data->listenv[i].value)
			printf("%s%s\n", data->listenv[i].name, data->listenv[i].value);
		i++;
	}
}

void	env_initialize(t_data *data, char **old_env)
{
	t_listenv		*listenv;
	char			**env;
	int				i;
	size_t			j;
	size_t			len;

	if (!data->env)
		data->env = (char **)malloc(sizeof(char *));
	i = 0;
	while (old_env[i])
		i++;
	data->env = old_env;
	env = data->env;
	if (data->listenv)
		free (data->listenv);
	if (!data->listenv)
		data->listenv = (t_listenv *)malloc(sizeof(t_listenv) * i + 1);
	listenv = data->listenv;
	i = 0;
	while (env[i])
	{
		j = 0;
		len = ft_strlen(env[i]);
		while (env[i][j] != '=')
			j++;
		listenv[i].name = ft_substr(env[i], 0, j);
		listenv[i].value = ft_substr(env[i], j, len - j);
		listenv[i].index = 1;
		i++;
	}
	data->env[i] = NULL;
}

void	env_built(t_data *data, char **env, int flag)
{
	env_initialize(data, env);
	if (!flag)
		env_print(data);
}

/* int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	env_built(data, env, 0);
} */
