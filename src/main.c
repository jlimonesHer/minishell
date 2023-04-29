#include "../includes/minishell.h"
#include <sys/stat.h>

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_command	*a;
	char		**env;
	char		**va_export;
	int si;

	si = 1;
	(void)argc;
	(void)argv;
	va_export = env_copy2(envp);
	env = env_copy2(envp);
	while (si)
	{
		signal(SIGINT, ft_signal);
		input = readline("> ");
		if (!input)
			si = ctrl_d(input);
		else
		{
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		else
		add_history(input);
		a = parser(input, env);
		if (a == NULL)
			continue ;
		free(input);
		executor(a, &env, &va_export);
		ft_free_struct(a);
		}
	system("leaks minishell");
	}
	return (0);
}

void	ft_free_struct(t_command	*a)
{
	int	i;

	i = 0;

	while (a[i].last != 1)
	{
		printf("aqui0\n");
		ft_freewords(-1, a[i].argv);
		printf("aqui2\n");
		if (a[i].infile)
			ft_freewords(-1, a[i].infile);
		printf("aqui3\n");
		if (a[i].outfile)
			ft_freewords(-1, a[i].outfile);
		printf("aqui4\n");
		if (a[i].delimiter)
			free(a[i].delimiter);
		printf("aqui5\n");
		if (a[i].double_out)
			free(a[i].double_out);
		printf("aqui6\n");
		if (a[i].double_in)
			free(a[i].double_in);
		printf("aqui7\n");
		i++;
	}
	free(a);
}
// void	ft_free_struct_pipe(t_fd_pipes	*pipe)
// {
// 	free(pipe->fdin);
// 	free(pipe->fdout);
// 	free(pipe->tmpin);
// 	free(pipe->tmpout);
// }
