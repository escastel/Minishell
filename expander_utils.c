/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:29:17 by escastel          #+#    #+#             */
/*   Updated: 2024/04/18 14:24:53 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_tmp(char **tmp, char *func)
{
	if (*tmp)
		*tmp = ft_strjoin(*tmp, func);
	else
		*tmp = func;
}

void	dollar(char **tmp, char *str, int *i, int *j)
{
	while (str[*i] != '$')
		*i += 1;
	if (*i > *j)
		fill_tmp(tmp, ft_substr(str, *j, *i - *j));
	*i += 1;
	*j = *i;
	while (str[*i] != '$' && str[*i] != '\''
		&& str[*i] != '\"' && str[*i] != '\0' && str[*i] != '/')
		*i += 1;
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
			*tmp = ft_strjoin(*tmp, ft_substr(str, i, ft_strlen(str) - i));
		return (0);
	}
	return (1);
}

void	simple_quote(char **tmp, char *str, int *i, int *j)
{
	if (str[*i] == '\'')
	{
		*i += 1;
		*j = *i;
		while (str[*i] != '\'' && str[*i] != '\0')
			*i += 1;
		if (*i > *j)
			fill_tmp(tmp, ft_substr(str, *j, *i - *j));
	}
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
