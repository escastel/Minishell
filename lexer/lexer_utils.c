/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:03:42 by escastel          #+#    #+#             */
/*   Updated: 2024/05/06 12:25:12 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_singlequote(t_data *data, char **line, char **str)
{
	(*str)[data->j] = **line;
	*line += 1;
	data->j += 1;
	if (!**line)
	{
		error_msg("michishell: missing quote");
		data->status = 1;
		return (1);
	}
	while (**line && **line != '\'')
	{
		(*str)[data->j] = **line;
		*line += 1;
		data->j += 1;
	}
	if (**line != '\'')
	{
		error_msg("michishell: missing quote");
		data->status = 1;
		return (1);
	}
	(*str)[data->j] = **line;
	*line += 1;
	data->j += 1;
	return (0);
}

int	ft_doublequote(t_data *data, char **line, char **str)
{
	(*str)[data->j] = **line;
	*line += 1;
	data->j += 1;
	if (!**line)
	{
		error_msg("michishell: missing quote");
		data->status = 1;
		return (1);
	}
	while (**line && **line != '\"')
	{
		(*str)[data->j] = **line;
		*line += 1;
		data->j += 1;
	}
	if (**line != '\"')
	{
		error_msg("michishell: missing quote");
		data->status = 1;
		return (1);
	}
	(*str)[data->j] = **line;
	*line += 1;
	data->j += 1;
	return (0);
}

int	ft_backlashes(t_data *data, char **line, char **str)
{
	while (**line && **line == '\\')
	{
		(*str)[data->j] = (*(*line + 1));
		*line += 2;
		data->j += 1;
	}
	return (0);
}

int	ft_quotes_and_lashes(t_data *data, char **line, char **str)
{
	ft_backlashes(data, &(*line), &(*str));
	if (**line == '\"')
		if (ft_doublequote(data, &(*line), &(*str)))
			return (1);
	if (**line == '\'')
		if (ft_singlequote(data, &(*line), &(*str)))
			return (1);
	return (0);
}
