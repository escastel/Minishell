/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:32:47 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/04/16 10:54:20 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_data *data, char *str, int i, int j)
{
	t_list 		*aux;
	t_listenv	*listenv;
	char		*tmp;

	aux = ((t_list *)data->listenv);
	tmp = NULL;
	if (i == -1)
	{
		while (aux)
		{
			listenv = ((t_listenv *)aux->content);
			if (!ft_strcmp(listenv->name, str, ft_strlen(str)))
				return (listenv->value + 1);
			aux = aux->next;
		}
	}
	else
	{
		tmp = ft_substr(str, j, i);
		while (aux)
		{
			listenv = ((t_listenv *)aux->content);
			if (!ft_strcmp(listenv->name, tmp, ft_strlen(str)))
				return (listenv->value + 1);
			aux = aux->next;
		}
	}
	return (NULL);
}

/* if (str[i + 1] == '?')
				g_status; */

// QUEDA LA IMPLEMENTACION DE LAS COMILLAS

static	void	expand(t_data *data, char *str, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	if (str[i] == '~' && (str[i + 1] == '/' || str[i + 1] == '\0'))
	{
		*tmp = get_env(data, "HOME", -1, -1);
		if (!*tmp)
			return ;
	}
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '\0')
			i++;
		if (str[i] == '$')
		{
			i++;
			if (str[0] != '$')
			{
				*tmp = ft_substr(str, 0, i - 1);
			}
			j = i;
			while (str[i] != ' ' && str[i] != '$' && str[i] != '\''
				&& str[i] != '\"' && str[i] != '\0')
				i++;
			if (*tmp)
				*tmp = ft_strjoin(*tmp, get_env(data, str, i, j));
			if (!*tmp)
			{
				*tmp = get_env(data, str, i, j);
				if (!*tmp)
					return ;
			}
			/* if (str[i])           //EN ESTE CASO ES CUANDO TENEMOS LA VARIABLE ENTRE COMILLAS, ej: dfsjhknfiohadfsj"$HOME"dfvvsgdfijj
			{
				j = i;
				while (str[i])
					i++;
				*tmp = ft_strjoin(*tmp, ft_substr(str, j, i - j));
			} */
		}
		i++;
	}
	if (!*tmp)
		*tmp = ft_strdup(str);
}

void	expander(t_data *data)
{
	t_cmds	*cmd;
	char	*tmp;
	int		i;

	cmd = ((t_cmds *)data->cmd->content);
	i = 0;
	while (cmd->full_cmd[i])
	{
		tmp = NULL;
		expand(data, cmd->full_cmd[i], &tmp);
		free(cmd->full_cmd[i]);
		if (tmp)
			cmd->full_cmd[i] = ft_strdup(tmp);
		if (!tmp)
			cmd->full_cmd[i] = NULL;
		if (cmd->full_cmd[i])
			printf("%s\n", cmd->full_cmd[i]);
		i++;
	}
}
