#include "../../includes/minishell.h"

/**
 * @brief Busca la ruta a los comandos pasados por argumentos.
 * Con split separamos las variables de entorno.
 * Con ft_strnstr, busco la palabra PATH y sino avanzo en las posiciones
 * de las variables de entorno.
 * Recorro todas las rutas encontradas hasta encontar la correcta.
 * @param envp variables de entrorno.
 * @param cmd comando del que buscar la ruta.
 * @return char* a ruta del comando
 */
char	*search_path(char **env, char *cmd)
{
	char	**paths;
	char	*path_cmd;
	char	*substr;

	cmd = *ft_split(cmd, ' ');
	while (*env && !ft_strnstr(*env, "PATH=", 5))
		env++;
	substr = ft_substr(*env, 5, ft_strlen(*env) - 5);
	paths = ft_split(substr, ':');
	substr = ft_strjoin("/", cmd);
	free(cmd);
	while (*paths)
	{
		path_cmd = ft_strjoin(*paths++, substr);
		if (!path_cmd)
			return (NULL);
		if (!access(path_cmd, F_OK))
		{
			free(substr);
			return (path_cmd);
		}
		free(path_cmd);
	}
	free(substr);
	return (NULL);
}

int	is_delim(t_command *cmds)
{
	int		fdpipe[2];
	char	*line;

	if (pipe(fdpipe) < 0)
		return (-1);
	line = readline("heredoc> ");
	while (ft_strncmp(line, *cmds->delimiter, ft_strlen(line) + 1))
	{
		ft_putstr_fd(line, fdpipe[1]);
		ft_putstr_fd("\n", fdpipe[1]);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	close(fdpipe[1]);
	return (fdpipe[0]);
}

/**
 * @brief 
 * 
 * @param cmds struct donde se guardan los comandos
 * @param env variables de entorno
 * @param i indice de comando
 * @return int pid de hijo creado
 */
int	ft_create_child(t_command *cmds, char ***env, char ***var_export)
{
	int		pid;
	char	*shell;
	int		lvl;

	lvl = ft_atoi(search_env("SHLVL", *env));
	if (exec_builtin(cmds->argv, env, var_export))
		return (-1);
	pid = fork();
	printf("hola\n");
	if (pid == 0 && *cmds->double_out != 1)
	{
		shell = search_path(*env, cmds->argv[0]);
		if (shell == NULL && !access(*cmds->argv, F_OK))
		{
			shell = search_env("PWD", *env);
			ft_export(ft_strjoin("SHLVL=", ft_itoa(++lvl)), env, var_export);
		}
		if (shell == NULL)
		{
			ft_putstr_fd(": command no found\n", 2);
			exit(-1);
		}
		execve(shell, &cmds->argv[0], *env);
	}
	return (pid);
}


