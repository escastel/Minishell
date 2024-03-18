/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:33:48 by escastel          #+#    #+#             */
/*   Updated: 2024/03/18 18:13:26 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_built(t_data *data, char *str)
{
	char		**env;
	int			i;
	int			n;

	i = 0;
	n = -1;
	env = data->env;
	/* env_built(data, env, 1); */
	while (env[i])
	{
		while (env[i][n] != '=')
			n++;
		if (ft_strncmp(env[i], str, n))
		{
			n = -1;
			i++;
		}
		else if (!ft_strncmp(env[i], str, n))
		{
			while (env[i + 1])
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i] = NULL;
		}
	}
}

/* int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		i;
	char	str[]="HOME";

	(void)argc;
	(void)argv;
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	i = 0;
	while (env[i])
		i++;
	data->env = (char **)malloc(sizeof(char *) * i + 1);
	if (!data->env)
		return (1);
	data->env = env;
	data->listenv = (t_listenv *)malloc(sizeof(t_listenv) * i + 1);
	if (!data->listenv)
		return (1);
	printf("ANTIGUO EXPORT:\n");
	export_built(data);
	unset_built(data, str);
	printf("\nNUEVO EXPORT:\n");
	export_built(data);
} */
