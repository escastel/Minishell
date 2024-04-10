/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:43:40 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/04/09 13:01:44 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_cmd(void *cmd)
{
	int	i;

	i = -1;
//	free (((t_cmds *)cmd)->builtin);
//	free (((t_cmds *)cmd)->outfile);
//	free (((t_cmds *)cmd)->infile);
//	if (ft_strlen((((t_cmds *)cmd)->exc_path)) != 0) // comand filter reserva y libera, me da poblemas
//	if (((t_cmds *)cmd)->exc_path)
//		free (((t_cmds *)cmd)->exc_path);
//	while (((t_cmds *)cmd)->full_cmd[++i])
//		free (((t_cmds *)cmd)->full_cmd[i]);
	free (((t_cmds *)cmd)->full_cmd);
}

void	ft_liberator(t_data *data)
{
//	free(data->pipe);
	ft_lstclear(&data->cmd, &ft_delete_cmd);
}
