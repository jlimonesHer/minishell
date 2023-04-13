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
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		a = parser(input, envp);
		if (a == NULL)
			continue ;
		add_history(input);
		free(input);
		j = 0;
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
		ft_free_struct(a);
		system("leaks minishell");
	}
}

void	ft_free_struct(t_command	*a)
{
	int	i;

	i = 0;
	while (a[i].last != 1)
	{
		ft_freewords(-1, a[i].argv);
		ft_freewords(-1, a[i].infile);
		ft_freewords(-1, a[i].outfile);
		free(a[i].double_out);
		i++;
	}
	free(a);
}
