/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airat_must <https://github.com/AirMust>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:37:02 by airat_must        #+#    #+#             */
/*   Updated: 2020/12/19 04:38:51 by airat_must       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/vm.h"

void get_op_code(t_vm *vm, t_process *proc)
{
	int code_id;

	code_id = get_byte_int(vm, PROC_POS, OP_CODE_LEN);
	// ft_printf("COde: %d, PROC: %d", code_id, PROC_POS);
	proc->id_op = code_id;
	if (code_id >= 1 && code_id <= OP_N_FUN)
		proc->cycle_op = g_op[code_id - 1].cycles;
}

void get_op_type_agrs(t_vm *vm, t_process *proc, t_op *op)
{
	int type_args;
	if (op->is_type_args)
	{
		type_args = get_byte_int(vm, PROC_POS + OP_CODE_LEN, ARGS_CODE_LEN);
		// ft_printf("NAME: %s, TY: %d-%d-%d",op->name, type_args, PROC_POS, op->args_num);
		if (op->args_num >= 1)
			proc->type_args[0] = g_type_args[((type_args & MASK_R) >> 6) - 1];
		if (op->args_num >= 2)
			proc->type_args[1] = g_type_args[((type_args & MASK_G) >> 4) - 1];
		if (op->args_num >= 3)
			proc->type_args[2] = g_type_args[((type_args & MASK_B) >> 2) - 1];
		// ft_printf("TA: %d %d %d\n", PROC_TA[0], PROC_TA[1], PROC_TA[2]);
		return;
	}
	proc->type_args[0] = op->type_args[0];
}

int gap_op_args(t_process *proc, t_op *op)
{
	int step;
	int i;

	i = -1;
	step = OP_CODE_LEN + (op->is_type_args ? ARGS_CODE_LEN : 0);
	while (++i < op->args_num)
	{
		step += get_step(proc->type_args[i], op);
	}
	return (step);
}

int get_op_args(t_vm *vm, t_process *proc, int index_arg, int is_mod)
{
	t_op *op;
	int32_t value;
	int addr;

	op = &g_op[proc->id_op - 1];
	value = 0;
	if (PROC_TA[index_arg - 1] & T_REG)
		value = PROC_REG[get_byte_int(vm, PROC_POS + PROC_STEP, 1) - 1];
	else if (PROC_TA[index_arg - 1] & T_DIR)
	{
		ft_printf("%d", PROC_POS + PROC_STEP);
		value = get_byte_int(vm, PROC_POS + PROC_STEP, op->t_dir_size);
	}else if (PROC_TA[index_arg - 1] & T_IND)
	{
		addr = get_byte_int(vm, PROC_POS + PROC_STEP, IND_SIZE);
		addr = is_mod ? (addr % IDX_MOD) : addr;
		value = get_byte_int(vm, PROC_POS + addr, DIR_SIZE);
	}
	PROC_STEP += (PROC_TA[index_arg - 1] == T_REG ? REG_LEN : PROC_TA[index_arg - 1] == T_DIR ? op->t_dir_size : IND_SIZE);
	return (value);
}
