/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:00:15 by escastel          #+#    #+#             */
/*   Updated: 2024/04/23 12:45:11 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	handler_backslash(void)
{
	printf("Quit: 3\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	handler(int signal)
{
	if (signal == SIGQUIT)
		handler_backslash();
	if (!g_signal)
	{
		printf("\033[K\n");
		rl_replace_line("", 0);
		g_signal = 1;
	}
	else if (g_signal == 2)
	{
		printf("\033[K\n");
		close (0);
		g_signal = 1;
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		printf("\033[K\n");
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
	}
} */
