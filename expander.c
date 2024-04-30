/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:32:47 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/04/30 19:01:04 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_util2(t_data *data, char **tmp, char *str, int *flag)
{
	if (str[data->i + 1] == '\"')
		fill_tmp(tmp, "");
	data->j = data->i + 1;
	*flag = 0;
	while (str[++data->i] != '\"' && str[data->i] != '\0')
	{
		if (str[data->i] == '$')
		{
			data->i = data->j;
			*flag = 1;
			if (!dollar(tmp, str, &data->i, &data->j))
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
			if (!dollar(tmp, str, &data->i, &data->j))
				fill_tmp(tmp, expand_var(data, str, data->i, data->j));
			if (str[data->i + 1] && str[data->i] != '\'' && str[data->i] != '\"')
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
	simple_quote(data, tmp, str);
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

void	expander(t_data *data, int i)
{
	char	*tmp;

	tmp = NULL;
	if (expand_tilde(data, &tmp, data->prompt[i]))
		expand(data, data->prompt[i], &tmp);
	if (data->prompt[i])
		free (data->prompt[i]);
	/* data->prompt[i] = NULL; */
	data->prompt[i] = ft_strdup(tmp);
	tmp = NULL;
	return ;
}
