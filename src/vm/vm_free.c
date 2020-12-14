/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antondob <antondob@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 20:00:53 by vcaterpi          #+#    #+#             */
/*   Updated: 2020/12/10 00:48:07 by antondob         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

void	stage_free(void **stage)
{
	if (!*stage)
		return ;
	free(*stage);
	*stage = NULL;
}

void	players_free(t_player **players)
{
	if (!*players)
		return ;
	free(*players);
	*players = NULL;
}

void	process_free(t_process **process)
{
	t_process *tmp;

	if (!*process)
		return ;
	while (*process)
	{
		tmp = *process;
		*process = (*process)->next;
		free(tmp);
	}
}

void vm_free(t_vm **vm)
{
	if (!*vm)
		return ;
	stage_free(&((*vm)->stage));
	players_free(&((*vm)->players));
	process_free(&((*vm)->processes));
	free(*vm);
	*vm = NULL;	
}