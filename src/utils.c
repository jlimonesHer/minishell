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
