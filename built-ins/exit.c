/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:24:54 by escastel          #+#    #+#             */
/*   Updated: 2024/05/06 13:12:30 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_built(t_data *data, char **cmd)
{
	int	i;

	minishell_print(1);
	if (cmd != NULL)
		if (cmd[0])
		{
			i = -1;
			while (cmd[0][++i])
			{
				if (!ft_isdigit(cmd[0][i]))
				{
					printf(RED);
					printf("michishell: exit: %s: numeric argument required\n",
						cmd[0]);
					printf(RESET);
					data->status = 255;
					break ;
				}
			}
		}
	clean_program(data);
	exit(0);
}
