/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:33:48 by escastel          #+#    #+#             */
/*   Updated: 2024/03/19 17:13:19 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_built(t_data *data, char **cmd)
{
	int			i;
	int			n;
	char		**env;

	i = 0;
	n = 0;
	env = data->env;
	if (!cmd[0])
		return ;
	while (env[i])
	{
		n = 0;
		n = ft_strlen(cmd[0]) - 1;
		if (!ft_strncmp(env[i], cmd[0], n))
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
