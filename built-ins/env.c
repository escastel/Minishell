/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:56:23 by escastel          #+#    #+#             */
/*   Updated: 2024/04/05 13:20:04 by escastel         ###   ########.fr       */
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
			printf("%s", listenv->name);
			printf("=%s\n", listenv->value + 1);
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
