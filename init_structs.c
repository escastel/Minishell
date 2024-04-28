/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:49:06 by escastel          #+#    #+#             */
/*   Updated: 2024/04/28 18:59:33 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_struct(t_data *data, char **env)
{
	char	buff[500];

	g_signal = 1;
	data->oldpwd = NULL;
	data->cmd = (t_list *)malloc(sizeof(t_list));
	data->cmd_path = NULL; //lo misom aquí hice, como ya van seguros (parece)
	data->prompt = NULL; //añadio nuevo, problema de memoria dinamica
	data->pwd = (char *)malloc(sizeof(char) * ft_strlen(getcwd(buff, 500) + 1));
	if (!data->pwd)
		return (1);
	data->pwd = ft_strdup(getcwd(buff, 500));
	if (env_initialize(data, env))
		return (1);
	return (0);
}
