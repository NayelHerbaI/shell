
#include "minishell.h"

void	init_struct(t_input *input)
{
	input->linebuffer = NULL;
	input->tokens = NULL;
	input->ast = NULL;
	input->nread = 0;
	input->exit_status = 0;
	input->again = 0;
	input->len = 0;
}

void	init_utils(t_utils *utils)
{
	utils->i = 0;
	utils->j = 0;
	utils->start = 0;
	utils->varname_start = 0;
	utils->end = 0;
	utils->varname_len = 0;
	utils->varcontent_len = 0;
	utils->varcontent_start = 0;
	utils->env_index = 0;
	utils->varname1 = NULL;
	utils->varcontent1 = NULL;
}

void	reset_iterators(t_utils *utils)
{
	utils->i = 0;
	utils->j = 0;
	utils->start = 0;
	utils->end = 0;
}
