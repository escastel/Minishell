/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:48:24 by escastel          #+#    #+#             */
/*   Updated: 2024/05/03 20:22:14 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_tmp_reservator(t_data *data)
{
	char	**tmp;
	int		i;

	i = 0;
	while (data->prompt[i])
		i += 1;
	tmp = ft_calloc(i + 1, sizeof(char *));
	return (tmp);
}

t_cmds	*ft_new_cmd_node(void)
{
	t_cmds		*command;

	command = ft_calloc(1, ((sizeof(t_cmds))));
	command->full_cmd = NULL;
	command->exc_path = NULL;
	command->outfile = 1;
	command->infile = 0;
	return (command);
}

void	ft_new_cmd(t_data *data)
{
	t_list	*new;
	t_cmds	*command;

	command = ft_new_cmd_node();
	new = ft_lstnew(command);
	data->cmd = new;
}

void	ft_next_node(t_data *data)
{
	t_cmds	*command;
	t_list	*new;

	command = ft_new_cmd_node();
	new = ft_lstnew(command);
	ft_lstadd_back(&data->cmd, new);
}
