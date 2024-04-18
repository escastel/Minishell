/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:32:47 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/04/18 14:22:59 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_util2(t_data *data, char **tmp, char *str, int *flag)
{
	data->i++;
	data->j = data->i;
	*flag = 0;
	while (str[data->i] != '\"' && str[data->i] != '\0')
	{
		if (str[data->i] == '$')
		{
			data->i = data->j;
			*flag = 1;
			dollar(tmp, str, &data->i, &data->j);
			fill_tmp(tmp, expand_var(data, str, data->i, data->j));
			if (str[data->i] != '\"' && str[data->i])
			{
				data->j = data->i;
				while (str[data->i] != '\"')
					data->i++;
				fill_tmp(tmp, ft_substr(str, data->j, data->i - data->j));
			}
			break ;
		}
		data->i++;
	}
	if (data->i > data->j && !*flag)
		fill_tmp(tmp, ft_substr(str, data->j, data->i - data->j));
}

static void	expand_util(t_data *data, char **tmp, char *str, int *flag)
{
	while (str[data->i] != '\'' && str[data->i] != '\"' && str[data->i] != '\0')
	{
		if (str[data->i] == '$')
		{
			data->i = data->j;
			*flag = 1;
			dollar(tmp, str, &data->i, &data->j);
			fill_tmp(tmp, expand_var(data, str, data->i, data->j));
			if (str[data->i] && str[data->i] != '\'' && str[data->i] != '\"')
			{
				data->j = data->i;
				while (str[data->i] != '\0' && str[data->i] != '\''
					&& str[data->i] != '\"')
					data->i++;
				fill_tmp(tmp, ft_substr(str, data->j, data->i - data->j));
			}
			break ;
		}
		data->i++;
	}
	if (data->i > data->j && !*flag)
		fill_tmp(tmp, ft_substr(str, data->j, data->i - data->j));
	simple_quote(tmp, str, &data->i, &data->j);
	if (str[data->i] == '\"')
		expand_util2(data, tmp, str, flag);
}

static void	expand(t_data *data, char *str, char **tmp)
{
	int	flag;

	data->i = 0;
	data->j = 0;
	while (str[data->i])
	{
		flag = 0;
		data->j = data->i;
		expand_util(data, tmp, str, &flag);
		data->i++;
	}
}

void	expander(t_data *data)
{
	t_cmds	*cmd;
	char	*tmp;
	int		i;

	i = 0;
	cmd = ((t_cmds *)data->cmd->content);
	tmp = NULL;
	while (cmd->full_cmd[i])
	{
		if (expand_tilde(data, &tmp, cmd->full_cmd[i]))
			expand(data, cmd->full_cmd[i], &tmp);
		if (cmd->full_cmd[i])
			free(cmd->full_cmd[i]);
		if (tmp)
			cmd->full_cmd[i] = ft_strdup(tmp);
		if (!tmp)
			cmd->full_cmd[i] = NULL;
		if (cmd->full_cmd[i])
			printf("%s\n", cmd->full_cmd[i]);
		tmp = NULL;
		i++;
	}
}
