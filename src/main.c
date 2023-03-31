#include "../includes/minishell.h"
#include <sys/stat.h>

static t_cmd_table	init_struct(char *input, int argc)
{
	t_cmd_table	cmds;
	char		**commands;
	int			i;

	commands = ft_split(input, '|');
	// TODO contar antes de reservar memoria
	cmds.cmds = malloc(50 * sizeof(t_command));
	i = 0;
	while (commands[i])
	{
		cmds.cmds[i].argv = ft_split(commands[i], ' ');
		cmds.cmds[i].argc = argc;
		i++;
	}
	cmds.n_cmds = i;
	free(commands);
	return (cmds);
}

int main(int ac, char **av, char **env)
{
	char		*input;
	char		**a;
	int			i;
	t_cmd_table	cmds;

	if (ac == 1 && av[0][0])
	{
		while (1)
		{
			i = 0;
			input = readline("> ");
			a = lexer(input);
			add_history(input);
			cmds = init_struct(input, ac);
			
			// while (cmds.cmds[i].argv[0])
			// {
			// 	printf("argv[%i] = %s\n", i, cmds.cmds[i].argv[i]);
			// 	i++;
			// }
			ft_one_cmd(&cmds, env);
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
