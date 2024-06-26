/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:29:17 by escastel          #+#    #+#             */
/*   Updated: 2024/05/03 20:39:45 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_tmp(char **tmp, char *func)
{
	if (*tmp)
	{
		*tmp = ft_strjoin_gnl(*tmp, func);
		free (func);
	}
	else
		*tmp = func;
}

int	dollar(char **tmp, char *str, t_data *data)
{
	while (str[data->i] != '$')
		data->i += 1;
	if (str[data->i] == '$' && (str[data->i + 1] == '\0'
			|| str[data->i + 1] == '\"' || str[data->i + 1] == '\''))
	{
		data->i += 1;
		fill_tmp(tmp, ft_substr(str, data->j, data->i - data->j));
		return (1);
	}
	if (str[data->i] == '$' && str[data->i + 1] == '?')
	{
		fill_tmp(tmp, ft_substr(str, data->j, data->i - data->j));
		fill_tmp(tmp, get_status(data));
		data->i += 2;
		return (1);
	}
	if (data->i > data->j)
		fill_tmp(tmp, ft_substr(str, data->j, data->i - data->j));
	data->i += 1;
	data->j = data->i;
	while (str[data->i] != ' ' && str[data->i] != '$' && str[data->i] != '\''
		&& str[data->i] != '\"' && str[data->i] != '\0' && str[data->i] != '/')
		data->i += 1;
	return (0);
}

int	expand_tilde(t_data *data, char **tmp, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '~' && (str[i + 1] == '/' || str[i + 1] == '\0'))
	{
		i++;
		*tmp = expand_var(data, "HOME", -1, -1);
		if (str[i] == '/' && *tmp && str[i])
			fill_tmp(tmp, ft_substr(str, i, ft_strlen(str) - i));
		return (0);
	}
	return (1);
}

char	*get_status(t_data *data)
{
	return (ft_itoa(data->status));
}

char	*expand_var(t_data *data, char *str, int i, int j)
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
		if (!ft_strncmp(((t_listenv *)aux->content)->name, tmp,
				ft_strlen(tmp) + 1))
		{
			if (((t_listenv *)aux->content)->value)
			{
				free (tmp);
				return (ft_strdup(((t_listenv *)aux->content)->value + 1));
			}
		}
		aux = aux->next;
	}
	free (tmp);
	return (ft_strdup(""));
}
