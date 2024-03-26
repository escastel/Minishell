/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:56:23 by escastel          #+#    #+#             */
/*   Updated: 2024/03/26 12:21:07 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	env_print(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (data->listenv[i].value + 1)
			printf("=%s\n", data->env[i]);
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
