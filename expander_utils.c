/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:29:17 by escastel          #+#    #+#             */
/*   Updated: 2024/04/17 19:09:47 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	check_quotes(char	*str, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strchr(str, '\''))
	{
		i++;
		while (str[i])
		{
			j = i;
			if (str[i] == '\'')
			{
				while (str[i] != '\'')
					i++;
				if (!*tmp)
					*tmp = ft_substr(str, j, i);
				else
					*tmp = ft_strjoin(*tmp, ft_substr(str, j, i));
			}
			i++;
		}
	}
	return ;
} */
/* if (str[i + 1] == '?')
				g_status; */

// QUEDA LA IMPLEMENTACION DE LAS COMILLAS

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

/* static void	expand_env(t_data *data, char *str, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '\0' || str[i + 1] == '\''|| str[i + 1] == '\"'))
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
			if (*tmp && get_env(data, str, i, j) != NULL)
				*tmp = ft_strjoin(*tmp, get_env(data, str, i, j));
			if (!*tmp)
			{
				*tmp = get_env(data, str, i, j);
				if (!*tmp)
					return ;
			}
			if (str[i])           //EN ESTE CASO ES CUANDO TENEMOS LA VARIABLE ENTRE COMILLAS, ej: dfsjhknfiohadfsj"$HOME"dfvvsgdfijj
			{
				j = i;
				while (str[i])
					i++;
				*tmp = ft_strjoin(*tmp, ft_substr(str, j, i - j));
			}
		}
		i++;
	}
	if (!*tmp)
		*tmp = ft_strdup(str);
} */

/* void	expander(t_data *data)
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
} */