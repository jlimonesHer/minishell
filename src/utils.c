#include "../includes/minishell.h"
/**
 * @brief la funcion sale si el parametro pasado es exit
 * 
 * @param cmd string del comando pasado desde shell
 */
void	ft_exit(char *cmd)
{
	if (!ft_strncmp(cmd, "exit", 4))
		exit(0);
}

void	free_quotes(t_expand *e)
{
	free(e->var);
	free(e->env);
	free(e->line);
	free(e->sub);
	e->var = NULL;
	e->env = NULL;
	e->line = NULL;
	e->sub = NULL;

}

void	free_first_quotes(t_expand *e)
{
	free(e->var);
	free(e->env);
	e->var = NULL;
	e->env = NULL;
}
