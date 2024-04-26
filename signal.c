/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:00:15 by escastel          #+#    #+#             */
/*   Updated: 2024/04/26 17:14:52 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler_backslash(void)
{
	printf("Quit: 3\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	handler(int signal)
{
	if (signal == SIGQUIT)
		handler_backslash();
	if (!g_signal)          //COMANDOS
	{
		write(1, "\033[K\n", 5);
		rl_replace_line("", 0);
		g_signal = 1;
	}
	else if (g_signal == 2) //HEREDOC
	{
		write(1, "\033[K\n", 5);
		close (0);
		g_signal = 1;
	}
	else                  //SIN COMANDOS
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		write(1, "\033[K\n", 5);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
	}
}
