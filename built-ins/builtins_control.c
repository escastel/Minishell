/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:02:19 by escastel          #+#    #+#             */
/*   Updated: 2024/03/21 16:22:44 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtins_control(t_data *data, char **env)
{
	int	n;

	n = ft_strlen(data->cmd[0]);
	if (!ft_strncmp(data->cmd[0], "cd", n))
		cd_built(data, data->cmd + 1);
	if (!ft_strncmp(data->cmd[0], "echo", n))
		echo_built(data->cmd + 1);
	if (!ft_strncmp(data->cmd[0], "env", n))
		env_built(data, data->cmd + 1);
	if (!ft_strncmp(data->cmd[0], "exit", n))
		exit_built();
	if (!ft_strncmp(data->cmd[0], "export", n))
		export_built(data, data->cmd + 1);
	if (!ft_strncmp(data->cmd[0], "pwd", n))
		pwd_built();
	if (!ft_strncmp(data->cmd[0], "unset", n))
		unset_built(data, data->cmd + 1);
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
