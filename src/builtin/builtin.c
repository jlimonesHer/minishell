#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char	buffer[1000];

	getcwd(buffer, 1000);
	printf("%s\n", buffer);
}

void	ft_echo(char **argv)
{
	int		i;

	i = -1;
	while (argv[1][++i])
		printf("%c", argv[1][i]);
	printf("\n");
}

int	exec_builtin(char **argv)
{
	int	build;

	build = 1;
	if (!ft_strncmp(argv[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(argv[0], "echo", 5))
		ft_echo(argv);
	else if (!ft_strncmp(argv[0], "cd", 3))
		printf("cd\n");
	else if (!ft_strncmp(argv[0], "export", 7))
		printf("export\n");
	else if (!ft_strncmp(argv[0], "unset", 6))
		printf("unset\n");
	else if (!ft_strncmp(argv[0], "env", 4))
		printf("env\n");
	else if (!ft_strncmp(argv[0], "exit", 5))
		printf("exit\n");
	else
		build = 0;
	return (build);
}
