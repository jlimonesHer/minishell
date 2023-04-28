#include "../../includes/minishell.h"

int	ctrl_c(char *input)
{
	if (!input)
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	return (1);
}

void	ft_signal(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  ", 1);
	ft_printf("\n");
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

//free de mas en env
//cd .. raiz es Desktop
