/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:32:47 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/04/17 19:07:59 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand(t_data *data, char *str, char **tmp)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	if (str[i] == '~' && (str[i + 1] == '/' || str[i + 1] == '\0'))
	{
		expand_tilde(data, str, tmp);
		if (!*tmp)
			return ;
	}
	while (str[i])
	{
		j = i;
		flag = 0;
		while (str[i] != '\'' && str[i] != '\"' && str[i] != '\0')
		{
			if (str[i] == '$')
			{
				i = j;
				flag = 1;
				while (str[i] != '$')
					i++;
				if (i > j)
				{
					if (!*tmp)
						*tmp = ft_substr(str, j, i - j);
					else
						*tmp = ft_strjoin(*tmp, ft_substr(str, j, i - j));
				}
				i++;
				j = i;
				while (str[i] != ' ' && str[i] != '$' && str[i] != '\''
					&& str[i] != '\"' && str[i] != '\0')
					i++;
				if (*tmp)
					*tmp = ft_strjoin(*tmp, get_var(data, str, i, j));
				else
					*tmp = get_var(data, str, i, j);
				break ;
			}
			i++;
		}
		if (i > j && !flag)
		{
			if (*tmp)
				*tmp = ft_strjoin(*tmp, ft_substr(str, j, i - j));
			else
				*tmp = ft_substr(str, j, i - j);
		}
		if (str[i] == '\'')
		{
			i++;
			j = i;
			while (str[i] != '\'' && str[i] != '\0')
				i++;
			if (i > j)
			{
				if (*tmp)
					*tmp = ft_strjoin(*tmp, ft_substr(str, j, i - j));
				else
					*tmp = ft_substr(str, j, i - j);
			}
		}
		flag = 0;
		if (str[i] == '\"')
		{
			i++;
			j = i;
			while (str[i] != '\"' && str[i] != '\0')
			{
				if (str[i] == '$')
				{
					i = j;
					flag = 1;
					while (str[i] != '$')
						i++;
					if (i > j)
					{
						if (!*tmp)
							*tmp = ft_substr(str, j, i - j);
						else
							*tmp = ft_strjoin(*tmp, ft_substr(str, j, i - j));
					}
					i++;
					j = i;
					while ((str[i] != ' ' && str[i] != '$' && str[i] != '\''
						&& str[i] != '\"' && str[i] != '\0'))
							i++;
					if (*tmp)
						*tmp = ft_strjoin(*tmp, get_var(data, str, i, j));
					else
						*tmp = get_var(data, str, i, j);
					if (str[i])
					{
						j = i;
						while (str[i] != '\"')
							i++;
						if (*tmp)
							*tmp = ft_strjoin(*tmp, ft_substr(str, j, i - j));
						else
							*tmp = ft_substr(str, j, i - j);
					}
					break ;
				}
				i++;
			}
			if (i > j && !flag)
			{
				if (*tmp)
					*tmp = ft_strjoin(*tmp, ft_substr(str, j, i - j));
				else
					*tmp = ft_substr(str, j, i - j);
			}
		}
		i++;
	}
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
		if (cmd->full_cmd[i])
			free(cmd->full_cmd[i]);
		if (tmp)
			cmd->full_cmd[i] = ft_strdup(tmp);
		if (!tmp)
			cmd->full_cmd[i] = NULL;
		if (cmd->full_cmd[i])
			printf("%s\n", cmd->full_cmd[i]);
		i++;
	}
	tmp = NULL;
}
