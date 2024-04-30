/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:40:47 by escastel          #+#    #+#             */
/*   Updated: 2024/04/30 18:41:41 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_new_var(t_data *data, char *str, int *flag)
{
	t_listenv	*new;
	t_list		*list;
	int			len;

	data->i = -1;
	list = data->listenv;
	while (data->env[++data->i] && list)
	{
		new = (t_listenv *)list->content;
		len = ft_strlen(new->name);
		if (!ft_strncmp(new->name, str, len))
		{
			data->j = 0;
			while (str[data->j] != '=' && str[data->j])
				data->j++;
			if (str[data->j] != '=')
				return (1);
			*flag = 0;
		}
		list = list->next;
	}
	return (0);
}

void	add_var_list(t_data *data, char *str)
{
	t_listenv	*new;
	t_list		*list;
	int			i;

	i = 0;
	new = (t_listenv *)malloc(sizeof(t_listenv));
	while (str[i] != '=' && str[i])
		i++;
	new ->name = ft_substr(str, 0, i);
	new->value = ft_substr(str, i, ft_strlen(str) - i);
	new->index = 1;
	list = ft_lstnew(new);
	ft_lstadd_back(&data->listenv, list);
}