/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:29:17 by escastel          #+#    #+#             */
/*   Updated: 2024/04/17 19:58:05 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(t_data *data, char *str, int i, int j)
{
	t_list		*aux;
	char		*tmp;

	aux = ((t_list *)data->listenv);
	tmp = NULL;
	if (i != -1 && j != -1)
		tmp = ft_substr(str, j, i - j);
	else
		tmp = ft_strdup(str);
	while (aux)
	{
		if (!ft_strcmp(((t_listenv *)aux->content)->name, tmp, ft_strlen(tmp)))
		{
			if (((t_listenv *)aux->content)->value)
			{
				if (!ft_strcmp(tmp, "OLDPWD", 6) || !ft_strcmp(tmp, "PWD", 3))
					return (((t_listenv *)aux->content)->value);
				else
					return (((t_listenv *)aux->content)->value + 1);
			}
		}
		aux = aux->next;
	}
	return ("");
}

void	expand_tilde(t_data *data, char *str, char **tmp)
{
	int	i;

	i = 1;
	*tmp = get_var(data, "HOME", -1, -1);
	if (str[i] == '/' && *tmp && str[i])
		*tmp = ft_strjoin(*tmp, ft_substr(str, i, ft_strlen(str) - i));
}
