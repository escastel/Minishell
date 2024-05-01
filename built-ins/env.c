/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:56:23 by escastel          #+#    #+#             */
/*   Updated: 2024/05/01 12:23:43 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_print(t_data *data)
{
	t_list		*aux;
	t_listenv	*listenv;
	int			i;

	i = 0;
	aux = data->listenv;
	while (data->env[i] && aux)
	{
		listenv = ((t_listenv *)aux->content);
		if (listenv->value)
		{
			if (!ft_strcmp(listenv->name, "PWD", ft_strlen(listenv->name))
				|| !ft_strcmp(listenv->name, "OLDWD", ft_strlen(listenv->name)))
				printf("%s=%s\n", listenv->name, listenv->value);
			else if (ft_strncmp(listenv->value, "", ft_strlen(listenv->value)))
				printf("%s=%s\n", listenv->name, listenv->value + 1);
		}
		aux = aux->next;
		i++;
	}
}

void	env_built(t_data *data, char **cmd)
{
	int	flag;

	flag = open(cmd[0], O_DIRECTORY);
	if (flag != -1)
	{
		printf("env: %s: Permission denied\n", cmd[0]);
		return ;
	}
	if (cmd[0])
	{
		printf("env: %s: No such file or directory\n", cmd[0]);
		return ;
	}
	env_print(data);
}
