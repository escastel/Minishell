/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:33:48 by escastel          #+#    #+#             */
/*   Updated: 2024/03/29 15:28:50 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_util(t_data *data, char *cmd)
{
	int			i;
	int			n;
	char		**env;

	i = 0;
	n = 0;
	env = data->env;
	if (!cmd)
		return ;
	while (env[i])
	{
		n = 0;
		n = ft_strlen(cmd) - 1;
		if (!ft_strncmp(env[i], cmd, n))
		{
			while (env[i])
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i] = NULL;
		}
		i++;
	}
	env_initialize(data, env);
}

void	unset_built(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		unset_util(data, cmd[i]);
		i++;
	}
}
