/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:40:47 by escastel          #+#    #+#             */
/*   Updated: 2024/05/01 15:16:25 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_str(t_data *data)
{
	data->i = -1;
	while (data->env[++data->i])
		free (data->env[data->i]);
	free (data->env);
}

void	reset_index(t_data *data)
{
	t_list		*list;
	t_listenv	*aux;

	list = data->listenv;
	while (list)
	{
		aux = (t_listenv *)list->content;
		aux->index = 1;
		list = list->next;
	}
}
