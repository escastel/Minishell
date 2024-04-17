/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:18:40 by escastel          #+#    #+#             */
/*   Updated: 2024/04/16 10:55:29 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*line;

	(void)argv;
	(void)env;
	if (argc != 1)
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	init_struct(data, env);
	minishell_print(0);
	while (1)
	{
		line = readline("michishell$ ");
		if (ft_strcmp(line, "\0", ft_strlen(line)))
			add_history(line);
		lexer(data, line);
		printf("lexer\n");
		expander(data);
		printf("expander\n");
		parser(data);
		printf("parser\n");
		dup2(((t_cmds *)data->cmd->content)->infile, STDIN_FILENO);
		printf("dup\n");
		ft_liberator(data);
		printf("liberator\n");
	}
	return (0);
}
