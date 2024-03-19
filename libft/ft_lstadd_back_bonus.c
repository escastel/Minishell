/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escastel <escastel@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:37:46 by escastel          #+#    #+#             */
/*   Updated: 2024/01/08 18:28:57 by escastel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_stack **lst, t_stack *new)
{
	t_stack	*back;

	back = *lst;
	if (!back)
	{
		*lst = new;
		return ;
	}
	while (back->next != 0)
		back = back->next;
	back->next = new;
	return ;
}
