#include "../includes/minishell.h"
#include <sys/stat.h>

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_command	*a;
	int			i;
	int			j;

	(void)argc;
	(void)argv;
	while (1)
	{
		i = 0;
		input = readline("> ");
		add_history(input);
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		a = parser(input, envp);
		if (a == NULL)
			continue ;
		free(input);
		j = 0;
		while (!a[j].last)
		{
			input = readline("minishell> ");
			add_history(input);
			a = parser(input);
			executor(a, envp);
		}
		ft_free_struct(a);
		// system("leaks minishell");
	}
}

void	ft_free_struct(t_command	*a)
{
	int	i;

	i = 0;
	while (a[i].last != 1)
	{
		ft_freewords(-1, a[i].argv);
		if (a[i].infile)
			ft_freewords(-1, a[i].infile);
		if (a[i].outfile)
			ft_freewords(-1, a[i].outfile);
		if (a[i].double_out)
			free(a[i].double_out);
		i++;
	}
	free(a);
}
