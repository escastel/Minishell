/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:29:37 by escastel          #+#    #+#             */
/*   Updated: 2024/03/19 16:18:29 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// OLDPWD DEBERIA DE ESTAR GUARDADO EN LA ESTRUCTURA, 
//	ESTOY SUPONIENDO QUE DEBERIA DE ESTAR DE ANTES EN "-"
// RECIBE LA LINEA DE COMANDOS COMO CADENA

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

static void	cd_built_util(t_data *data, char *str, int flag)
{
	char	*buff;
	char	*tmp;

	buff = NULL;
	if (!flag)
	{
		data->oldpwd = getcwd(buff, 500);
		chdir("/Users/escastel");
	}
	if (flag == 1)
	{
		tmp = getcwd(buff, 500);
		chdir(data->oldpwd);
		printf("%s\n", data->oldpwd);
		data->oldpwd = tmp;
	}
	else if (flag == 2)
	{
		data->oldpwd = getcwd(buff, 500);
		chdir(str);
	}
}

void	cd_built(t_data *data, char **cmd)
{
	if (!cmd[0] || (cmd[0][0] == '~' && !cmd[0][1] && !cmd[1]))
	{
		cd_built_util(data, cmd[0], 0);
		return ;
	}
	if (cmd[0][0] == '-' && !cmd[0][1] && !cmd[1])
	{
		if (!data->oldpwd)
		{
			printf("michishell: cd: OLDPWD not set\n");
			return ;
		}
		else
			cd_built_util(data, cmd[0], 1);
	}
	else if (!cmd[1])
	{
		if (cd_error(cmd[0]))
			return ;
		cd_built_util(data, cmd[0], 2);
	}
}
