#include "../includes/minishell.h"
#include <sys/stat.h>

void	ft_echo(int ac, char **args)
{
	int	n;
	int	i;

	n = 0;
	i = 1;
	if (ac > 1 && !ft_strncmp("-n", args[i], 3))
	{
		n = 1;
		i++;
	}
	while (i < ac)
	{
		ft_putstr_fd(args[i], 1);
		if (i < ac - 1)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
}

int main()
{
    while (1)
    {
        char *input;
        char **a;
        int     i;

        i = 0;
        	input[i] = readline("minishell> ");
		while (input[i])
		{
			i++;
		}
        a = lexer(*input);
        add_history(*input);
        // while (a && a[i])
        // {
        //     printf("%s\n", a[i]);
        //     i++;
        // }
		printf("%s\n", input[0]);
		if (!ft_strncmp("echo", input[0], 5))
			ft_echo(2, a);
        ft_exit(input[0]);
    }
}
