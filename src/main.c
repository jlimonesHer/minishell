#include "../includes/minishell.h"
#include <sys/stat.h>

int main(int argc, char **argv, char **envp)
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
		a = parser(input, envp);
		add_history(input);
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
		// system("leaks minishell");
	}
}
