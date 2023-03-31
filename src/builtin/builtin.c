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
	int		j;
	int		new_line;

	new_line = 1;
	i = -1;
	j = 0;
	if (!ft_strncmp(argv[1], "-n", 2))
	{
		new_line = 0;
		j++;
	}
	while (argv[++j])
	{
		while (argv[j][++i])
		{
			printf("%c", argv[j][i]);
		}
		printf(" ");
		i = -1;
	}
	if (new_line)
		printf("\n");
}

static	void	ft_cd(char **argv)
{
	char	buffer[256];
	char	*path;

	getcwd(buffer, 256);
	//search_path("PWD", )
	path = ft_strjoin(buffer, "/");
	path = ft_strjoin(path, argv[1]);
	if (chdir(argv[1]) < 0)
		perror("Error");
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
		ft_cd(argv);
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
