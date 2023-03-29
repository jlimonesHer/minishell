#include "../includes/minishell.h"
#include <sys/stat.h>

static t_comand init_struct(char *input, int argc)
{
	t_comand cmd;

	cmd.argv = ft_split(input, ' ');
	cmd.argc = argc;
	return (cmd);
}

int main(int ac, char **av, char **env)
{
	char		*input;
	char		**a;
	int			i;
	t_comand	args;

	if (ac == 1 && av[0][0])
	{
		while (1)
		{
			i = 0;
			input = readline("jlimones> ");
			a = lexer(input);
			printf("input = %s\n", input);
			add_history(input);
			args = init_struct(input, ac);
			while (args.argv[i])
			{
				printf("argv[%i] = %s\n", i, args.argv[i]);
				i++;
			}
			ft_one_cmd(&args, env);
			// while (a && a[i])
			// {
			// 	printf("%s\n", a[i]);
			// 	i++;
			// }
		}
	}
}

// int	main(int ac, char **av, char **env)
// {
// 	if (ac > 0)
// 		ft_one_cmd(av, env);
// 	return 0;
// }
