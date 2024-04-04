/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:33:48 by escastel          #+#    #+#             */
/*   Updated: 2024/04/04 12:45:36 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_util_string(t_data *data, char **new_env, char *cmd, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], cmd, len))
		{
			new_env[j] = ft_strdup(data->env[i]);
			i++;
			j++;
		}
		else if (!ft_strncmp(data->env[i], cmd, len))
			i++;
	}
	new_env[j] = NULL;
	env_initialize(data, new_env);
	i = 0;
	while (new_env[i])
	{
		free(new_env[i]);
		i++;
	}
	free(new_env);
}

void	unset_util(t_data *data, char *cmd)
{
	int			i;
	int			j;
	int			len;
	char		**new_env;

	if (!cmd)
		return ;
	i = 0;
	j = 0;
	len = ft_strlen(cmd) - 1;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], cmd, len))
			j++;
		i++;
	}
	if (!j)
		return ;
	new_env = (char **)malloc(sizeof(char *) * i - j + 1);
	if (!new_env)
		return ;
	ft_lstclear(&data->listenv, del_listenv);
	free (data->listenv);
	unset_util_string(data, new_env, cmd, len);
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
