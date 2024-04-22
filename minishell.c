/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:18:40 by escastel          #+#    #+#             */
/*   Updated: 2024/04/22 14:39:55 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*line;

	(void)argv;
	if (argc != 1)
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
	init_struct(data, env);
	minishell_print(0);
	while (1)
	{
		line = readline("michishell$ ");
		if (ft_strcmp(line, "\0", ft_strlen(line)))
			add_history(line);
		lexer(data, line);
		expander(data);
		parser(data);
		// igual hace falta un free line
		ft_liberator(data);
	}
	return (0);
}
