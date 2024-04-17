/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:02:19 by escastel          #+#    #+#             */
/*   Updated: 2024/04/17 19:18:56 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtins_control(t_data *data, char **full_cmd)
{
	int	n;

	n = ft_strlen(full_cmd[0]);
	if (ft_strncmp(full_cmd[0], "cd", n) == 0)
		cd_built(data, full_cmd + 1);
	if (ft_strncmp(full_cmd[0], "echo", n) == 0)
		echo_built(full_cmd + 1);
	if (ft_strncmp(full_cmd[0], "env", n) == 0)
		env_built(data, full_cmd + 1);
	if (ft_strncmp(full_cmd[0], "exit", n) == 0)
		exit_built();
	if (ft_strncmp(full_cmd[0], "export", n) == 0)
		export_built(data, full_cmd + 1);
	if (ft_strncmp(full_cmd[0], "pwd", n) == 0)
		pwd_built();
	if (ft_strncmp(full_cmd[0], "unset", n) == 0)
		unset_built(data, full_cmd + 1);
}

/* int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argc;
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->cmd = argv + 1;
	builtins_control(data, env);
} */
