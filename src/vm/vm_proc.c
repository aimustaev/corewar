/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_proc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airat_must <https://github.com/AirMust>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 19:15:45 by airat_must        #+#    #+#             */
/*   Updated: 2020/12/18 19:24:10 by airat_must       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/vm.h"

void proc_step(t_process *proc)
{
	PROC_POS = mod_position(PROC_POS + PROC_STEP);
	PROC_STEP = 0;
	ft_bzero(proc->type_args, 3);
}
