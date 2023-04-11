#include "../includes/minishell.h"
#include <sys/stat.h>

int main(int ac, char **av, char **env)
{
	char			*input;
	t_command		*a;

	if (ac == 1 && av[0][0])
	{
		while (1)
		{
			
			input = readline("minishell> ");
			add_history(input);
			a = parser(input);
			ft_one_cmd(a, env);
		}
	}
}