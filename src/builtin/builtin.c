#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	ft_putendl_fd(buffer, 1);
	free(buffer);
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
	if (!argv[1])
	{
		chdir(getenv("HOME"));
		return ;
	}
	path = ft_strjoin(buffer, "/");
	path = ft_strjoin(path, argv[1]);
	if (chdir(argv[1]) < 0)
	{
		ft_putstr_fd(("cd: no such file or directory: "), 2);
		ft_putstr_fd(ft_strjoin(argv[1], "\n"), 2);
	}
}

void	ft_env(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}

int	exec_builtin(char **argv, char ***envp, char ***var_export)
{
	int	is_build;

	is_build = 1;
	if (!ft_strncmp(argv[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(argv[0], "echo", 5))
		ft_echo(argv);
	else if (!ft_strncmp(argv[0], "cd", 3))
		ft_cd(argv);
	else if (!ft_strncmp(argv[0], "export", 7))
		ft_export(argv[1], envp, var_export);
	else if (!ft_strncmp(argv[0], "unset", 6))
		printf("unset\n");
	else if (!ft_strncmp(argv[0], "env", 4))
		ft_env(*envp);
	else if (!ft_strncmp(argv[0], "exit", 5))
		printf("exit\n");
	else
		is_build = 0;
	return (is_build);
}
