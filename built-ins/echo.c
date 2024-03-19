/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:26:15 by escastel          #+#    #+#             */
/*   Updated: 2024/03/19 16:18:35 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_built(char **cmd)
{
	int	flag;
	int	i;

	i = 0;
	if (!cmd[0])
	{
		printf("\n");
		return ;
	}
	flag = 0;
	if (cmd[0][0] == '-' && cmd[0][1] == 'n' && !cmd[0][2])
	{
		flag = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
}
