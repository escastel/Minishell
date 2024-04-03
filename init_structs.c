/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:49:06 by escastel          #+#    #+#             */
/*   Updated: 2024/04/03 18:01:39 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_struct(t_data *data, char **env)
{
	/* t_list	*aux; */
	/* int	i; */

	if (env_initialize(data, env))
		return (1);
	if (fill_listenv(data, data->env))
		return (1);
	/* printf("ENV ANTESSSSS\n");
	i = -1;
	while(data->env[++i])
		printf("%s\n", data->env[i]); */
	/* aux = data->listenv;
	while (aux)
	{
		printf("%s%s\n", ((t_listenv *)aux->content)->name, ((t_listenv *)aux->content)->value);
		aux = aux->next;
	} */
	/* printf("\n\n\n\n\n"); */
	unset_util(data, "OLDPWD");
	/* printf("ENV DESPUESSSS\n");
	i = -1;
	while(data->env[++i])
		printf("%s\n", data->env[i]); */
	/* aux = data->listenv;
	while (aux)
	{
		printf("%s%s\n", ((t_listenv *)aux->content)->name, ((t_listenv *)aux->content)->value);
		aux = aux->next;
	} */
	data->cmd = (t_list *)malloc(sizeof(t_list *));
	if (!data->cmd)
		return (1);
	return (0);
}
