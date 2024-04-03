/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:18:40 by escastel          #+#    #+#             */
/*   Updated: 2024/04/03 16:36:35 by lcuevas-         ###   ########.fr       */
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
		line = readline("michishell$");
		lexer(data, line);
	}
	return (0);
}
