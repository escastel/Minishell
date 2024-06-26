/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:18:40 by escastel          #+#    #+#             */
/*   Updated: 2024/05/07 15:36:25 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	ft_leaks(void)
{
	system("leaks -q minishell");
} */

int	error_msg(char	*str)
{
	printf(RED "%s\n" RESET, str);
	return (1);
}

static void	minishell_loop(t_data *data)
{
	data->line = readline(CYAN "michishell$ " RESET);
	if (!data->line)
		exit_built(data, NULL);
	if (ft_strcmp(data->line, "", ft_strlen(data->line)))
	{
		add_history(data->line);
		if (!lexer(data, data->line))
		{
			if (!parser(data))
			{
				executer(data);
				clean_cmd(data);
			}
		}
	}
	free(data->line);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argv;
	if (argc != 1)
		return (error_msg("Error:\n This program does not need arguments\n"));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
	init_struct(data, env);
	minishell_print(0);
	while (1)
		minishell_loop(data);
	return (0);
}
