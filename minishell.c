/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:18:40 by escastel          #+#    #+#             */
/*   Updated: 2024/04/24 15:06:34 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	error_msg(char	*str)
{
	printf(RED "%s\n" RESET, str);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	atexit(ft_leaks);
	(void)argv;
	if (argc != 1)
		return (error_msg("Error:\n This program does not need arguments\n"));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	/* signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler); */
	init_struct(data, env);
	minishell_print(0);
	while (1)
	{
		data->line = readline(CYAN "michishell$ " RESET);
		if (ft_strcmp(data->line, "\0", ft_strlen(data->line)))
		{
			add_history(data->line);
			lexer(data, data->line);
			free(data->line);
			expander(data);
			parser(data);
			/* ft_liberator(data); */
		}
	}
	return (0);
}
