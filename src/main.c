#include "../includes/minishell.h"
#include <sys/stat.h>

int main(int ac, char **av, char **env)
{
	char			*input;
	t_command		*a;
	char			**envp;
	char			**var_export;

	envp = env_copy(env);
	var_export = env_copy(env);
	if (ac == 1 && av[0][0])
	{
		while (1)
		{
			input = readline("minishell> ");
			add_history(input);
			a = parser(input);
			executor(a, envp, var_export);
		}
	}
}
