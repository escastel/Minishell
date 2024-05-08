/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:00:15 by escastel          #+#    #+#             */
/*   Updated: 2024/05/08 12:53:26 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handler_backslash(void)
{
	write(1, "Quit: 3\n", 9);
 	rl_on_new_line();
	rl_replace_line("", 0);	
}

static void	handler_util(void)
{
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
	write(1, "\033[K\n", 5);
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
}

void	handler(int signal)
{
	if (signal == SIGQUIT)
	{
		handler_backslash();
		return ;
	}
	if (!g_signal)
	{
		write(1, "\033[K\n", 5);
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 1;
	}
	else if (g_signal == 2)
	{
		write(1, "\033[K\n", 5);
		rl_replace_line("", 0);
		rl_redisplay();
		close (0);
		g_signal = 1;
	}
	else
		handler_util();
}
