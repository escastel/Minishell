/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:33:48 by escastel          #+#    #+#             */
/*   Updated: 2024/04/03 18:01:16 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_util(t_data *data, char *cmd)
{
	int			i;
	int			j;
	int			n;
	char		**new_env;

	if (!cmd)
		return ;
	i = 0;
	j = 0;
	n = ft_strlen(cmd) - 1;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], cmd, n))
			j++;
		i++;
	}
	if (!j)
		return ;
	new_env = (char **)malloc(sizeof(char *) * i - j);
	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], cmd, n))
		{
			new_env[j] = ft_strdup(data->env[i]);
			i++;
			j++;
		}
		else if (!ft_strncmp(data->env[i], cmd, n))
			i++;
	}
	env_initialize(data, new_env);
	i = 0;
	while (new_env[i])
	{
		free(new_env[i]);
		i++;
	}
	free(new_env);
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
