#include "../includes/minishell.h"

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
char	*search_path(char **envp, char *cmd)
{
	char	**paths;
	char	*path_cmd;
	char	*substr;

	cmd = *ft_split(cmd, ' ');
	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	substr = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
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

void	ft_one_cmd(t_comand *args, char **env)
{
	char	*shell;
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		shell = search_path(env, *args->argv);
		if (shell == NULL)
		{
			ft_putstr_fd(*args->argv, 2);
			ft_putstr_fd(": command no found\n", 2);
			exit(-1);
		}
		execve(shell, args->argv, env);
		perror("Error: ");
		exit(-1);
	}
	waitpid(pid, &status, 0);
}
