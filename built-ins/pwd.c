/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:53:09 by escastel          #+#    #+#             */
/*   Updated: 2024/03/19 16:19:11 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//FUNCIONES PROTOTIPO, FUNCIONA
//PARA EL TAMANO EXACTO DE PWD, PODEMOS GUARDARLO EN UN INDICE CUANDO LEAMOS ENV

void	pwd_built(void)
{
	char	*buf;
	char	*pwd;

	buf = NULL;
	pwd = getcwd(buf, 500);
	printf("%s\n", pwd);
}
