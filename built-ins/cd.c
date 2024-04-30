/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:29:37 by escastel          #+#    #+#             */
/*   Updated: 2024/04/30 16:27:34 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_error(char *str)
{
	int	flag;

	flag = open(str, O_EXCL);
	if (flag == -1)
	{
		printf("michishell: cd: %s: No such file or directory\n", str);
		return (flag);
	}
	flag = open(str, O_DIRECTORY);
	if (flag == -1)
	{
		printf("michishell: cd: %s: Not a directory\n", str);
		return (flag);
	}
	return (0);
}

static void	cd_built_path(t_data *data, char *str)
{
	char	buff[500];

	if (data->oldpwd)
		free (data->oldpwd);
	data->oldpwd = ft_strdup(getcwd(buff, 500));
	chdir(str);
	if (data->pwd)
		free (data->pwd);
	data->pwd = ft_strdup(getcwd(buff, 500));
	/* env_initialize(data, data->env); */
}

static void	cd_built_oldpwd(t_data *data)
{
	char	buff[500];
	char	*tmp;

	tmp = ft_strdup(getcwd(buff, 500));
	chdir(data->oldpwd);
	printf("%s\n", data->oldpwd);
	if (data->oldpwd)
		free (data->oldpwd);
	data->oldpwd = ft_strdup(tmp);
	free (tmp);
	if (data->pwd)
		free (data->pwd);
	data->pwd = ft_strdup(getcwd(buff, 500));
	/* env_initialize(data, data->env); */
}

void	cd_built(t_data *data, char **cmd)
{
	if (cmd[0][0] == '-' && !cmd[0][1] && !cmd[1])
	{
		if (!data->oldpwd)
		{
			printf("michishell: cd: OLDPWD not set\n");
			return ;
		}
		else
		{
			cd_built_oldpwd(data);
			return ;
		}
	}
	else if (!cmd[1])
	{
		if (cd_error(cmd[0]))
			return ;
		cd_built_path(data, cmd[0]);
		return ;
	}
}
