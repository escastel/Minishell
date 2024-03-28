/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:32:47 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/03/27 10:54:11 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_data *data)
{
	(void)data;
// hay que recortar comillas y expandir los dolares y creo que poco mas,
// se podria quiza coloar alguna flag pero ya estamos igua.
// quiza este sea un buen punto para comprobar las pipes y empezar a partir
// si vamos a doble puntero las pipes hay que hacerlas antesp orque "partir" cmd
// es un poblema a esta altura. O quiza se pueda reciclar el espacio de la / pa
// meter la direccion del siguiente cmd struct
}
