/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:49:06 by escastel          #+#    #+#             */
/*   Updated: 2024/04/23 15:14:45 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_struct(t_data *data, char **env)
{
	char	buff[500];

	g_signal = 1;
	data->oldpwd = NULL;
	data->cmd = (t_list *)malloc(sizeof(t_list));
	data->cmd_path = (char **)malloc(sizeof(char *));
	data->pwd = (char *)malloc(sizeof(char) * ft_strlen(getcwd(buff, 500) + 1));
	if (!data->pwd)
		return (1);
	data->pwd = ft_strdup(getcwd(buff, 500));
	if (env_initialize(data, env))
		return (1);
	return (0);
}
