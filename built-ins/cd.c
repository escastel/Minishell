/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:29:37 by escastel          #+#    #+#             */
/*   Updated: 2024/03/18 14:54:44 by escastel         ###   ########.fr       */
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

static void	cd_built_util(char *str, int flag)
{
	char	*buff;
	char	*pwd;    //Estructura t_data
	char	*oldpwd; //Estructura t_data
	char	*tmp;

	buff = NULL;
	if (!flag)
	{
		oldpwd = getcwd(buff, 500);
		chdir("/Users/escastel");
	}
	if (flag == 1)
	{
		tmp = getcwd(buff, 500);
		chdir(oldpwd);
		printf("%s\n", oldpwd);
		oldpwd = tmp;
	}
	else if (flag == 2)
	{
		oldpwd = getcwd(buff, 500);
		chdir(str);
	}
	pwd = getcwd(buff, 500);
}

void	cd_built(char *str)
{
	char	*buff;
	char	*oldpwd; //Estructura t_data

	buff = NULL;
	oldpwd = NULL;
	if (!str || (str && str[0] == '~' && !str[1]))
	{
		cd_built_util(str, 0);
	}
	if (str && str[0] == '-' && !str[1])
	{
		if (!oldpwd)
		{
			printf("michishell: cd: OLDPWD not set\n");
			return ;
		}
		else
			cd_built_util(str, 1);
	}
	else
	{
		if (cd_error(str))
			return ;
		cd_built_util(str, 2);
	}
}

/* int	main(int argc, char **argv)
{
	(void)argc;
	cd_built(argv[1]);
	return (0);
} */
