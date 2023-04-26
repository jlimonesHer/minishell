#include "../includes/minishell.h"
#include <sys/stat.h>

void	free_env(char **env);

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_command	*a;
	char		**env;
	char		**va_export;

	(void)argc;
	(void)argv;
	va_export = env_copy(envp);
	env = env_copy(envp);
	while (1)
	{
		signal(SIGINT, ft_signal);
		input = readline("> ");
		ctrl_c(input);
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		else
			add_history(input);
		a = parser(input, env);
		int j = 0;
		int i;
		while (!a[j].last)
		{
			printf("Comando %d\n", j);
			i = 0;
			while (a[j].argv && a[j].argv[i])
			{
				printf("%s\n", a[j].argv[i]);
				i++;
			}
			j++;
		}
		if (a == NULL)
			continue ;
		free(input);
		executor(a, &env, &va_export);
		env = env_copy(env);
		va_export = env_copy(va_export);
		ft_free_struct(a);
		//system("leaks minishell");
	}
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
