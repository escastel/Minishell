/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:18:40 by escastel          #+#    #+#             */
/*   Updated: 2024/04/09 17:39:57 by lcuevas-         ###   ########.fr       */
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
		printf("posREADLINE\n");
		lexer(data, line);
		parser(data);
/* 		int	i = -1;
		while (data->cmd)
		{
			while (((t_cmds *)data->cmd->content)->full_cmd[++i])
				printf("%s\n", ((t_cmds *)data->cmd->content)->full_cmd[i]);
			data->cmd = data->cmd->next;
			i = -1;
			printf("pasandoasiguientelista\n");
		} */
		dup2(((t_cmds *)data->cmd->content)->infile, STDIN_FILENO);
		ft_liberator(data);
	}
	return (0);
}
