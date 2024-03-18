/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:26:15 by escastel          #+#    #+#             */
/*   Updated: 2024/03/18 15:03:16 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_built(char **str)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	if (!str[0])
	{
		printf("\n");
		return ;
	}
	if (str[0][0] == '-')
	{
		if (str[0][1] == 'n' && !str[0][2])
		{
			flag = 1;
			i++;
		}
	}
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
}

/* int	main(int argc, char **argv)
{
	(void)argc;
	echo_built(argv + 1);
} */
