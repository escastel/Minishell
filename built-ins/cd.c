/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:29:37 by escastel          #+#    #+#             */
/*   Updated: 2024/05/03 16:34:48 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_var(t_data *data)
{
	t_list		*list;
	t_listenv	*aux;

	list = data->listenv;
	while (list)
	{
		aux = (t_listenv *)list->content;
		if (!ft_strncmp(aux->name, "PWD", ft_strlen(aux->name)))
		{
			free (aux->value);
			aux->value = ft_strdup("=");
			aux->value = ft_strjoin_gnl(aux->value, data->pwd);
		}
		if (!ft_strncmp(aux->name, "OLDPWD", ft_strlen(aux->name)))
		{
			free (aux->value);
			aux->value = ft_strdup("=");
			aux->value = ft_strjoin_gnl(aux->value, data->oldpwd);
		}
		list = list->next;
	}
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
	update_var(data);
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
	update_var(data);
}

static int	cd_error(char *str)
{
	int	flag;

	flag = open(str, O_EXCL);
	if (flag == -1)
	{
		printf(RED);
		printf("michishell: cd: %s: No such file or directory\n", str);
		printf(RESET);
		return (1);
	}
	flag = open(str, O_DIRECTORY);
	if (flag == -1)
	{
		printf(RED);
		printf("michishell: cd: %s: Not a directory\n", str);
		printf(RESET);
		return (1);
	}
	return (0);
}

void	cd_built(t_data *data, char **cmd)
{
	char	*str;

	if (cmd[0])
		str = ft_strdup(cmd[0]);
	if (!cmd[0])
		str = expand_var(data, "HOME", -1, -1);
	if (str[0] == '-' && !str[1])
	{
		if (!data->oldpwd)
		{
			data->status = 1;
			printf(RED);
			printf("michishell: cd: OLDPWD not set\n");
			printf(RESET);
		}
		if (data->oldpwd)
			cd_built_oldpwd(data);
		return ;
	}
	data->status = cd_error(str);
	if (!data->status)
		cd_built_path(data, str);
	if (str)
		free (str);
	return ;
}
