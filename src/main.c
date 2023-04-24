#include "../includes/minishell.h"
#include <sys/stat.h>

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_command	*a;
	char		**env;
	char		**va_export;
	int si;
	//int i = -1;

	si = 1;
	(void)argc;
	(void)argv;
	va_export = env_copy2(envp);
	env = env_copy2(envp);
	while (si)
	{
		//signal(SIGINT, ft_signal);
		input = readline("> ");
		if (!input)
			si = ctrl_c(input);
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
		printf("ft = %i\n", *a->double_in);
		if (a == NULL)
			continue ;
		free(input);
		executor(a, &env, &va_export);
		env = env_copy1(env);
		va_export = env_copy1(va_export);
		ft_free_struct(a);
		}
	//system("leaks minishell");
	}
	return (0);
}

void	free_env(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
		free(env[i]);
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
		if (a[i].delimiter)
			ft_freewords(-1, a[i].delimiter);
		if (a[i].double_out)
			free(a[i].double_out);
		if (a[i].double_in)
			free(a[i].double_in);
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
