/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:43:40 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/04/26 16:39:56 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_delete_cmd(void *cmd)
{
	int	i;

	i = 0;
	if (((t_cmds *)cmd)->exc_path)
		free (((t_cmds *)cmd)->exc_path); // hay que ahcer la revisi'on ejor
	if (((t_cmds *)cmd)->infile != 0)
		close(((t_cmds *)cmd)->infile);
	if (((t_cmds *)cmd)->outfile != 1)
		close(((t_cmds *)cmd)->outfile);
 	while (((t_cmds *)cmd)->full_cmd[i])
	{
		free (((t_cmds *)cmd)->full_cmd[i]);
		i += 1;
	} 
	free (((t_cmds *)cmd)->full_cmd);
	free (cmd);
}

void	clean_cmd(t_data *data)
{
	int	i;

	i = 3;
	while (i <= 255)
	{
		close (i);
		i += 1;
	}
	ft_lstclear(&data->cmd, &ft_delete_cmd);

}
