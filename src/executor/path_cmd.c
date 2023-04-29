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
char	*search_path(char **env, char *cmd, int i)
{
	char	**paths;
	char	*path_cmd;
	char	*substr;
	char	*substr_f;
	//char	*cmd2;

//	cmd2 = ft_split(cmd, ' ');
	while (*env && !ft_strnstr(*env, "PATH=", 5))
		env++;
	substr_f = ft_substr(*env, 5, ft_strlen(*env) - 5);
	paths = ft_split(substr_f, ':');
	free(substr_f);

	substr = ft_strjoin("/", cmd);
	//free(cmd2);
	while (paths[i])
	{
		path_cmd = ft_strjoin(paths[i++], substr);
		if (!path_cmd)
			return (free(substr), ft_freewords(-1, paths), NULL);
		if (!access(path_cmd, F_OK))
			return (free(substr), ft_freewords(-1, paths), path_cmd);
		free(path_cmd);
	}
	return (free(substr), ft_freewords(-1, paths), NULL);
}

int	is_delim(t_command *cmds, t_fd_pipes *t_pipe)
{
	int		fdpipe[2];
	char	*line;
	int		i;

	if (pipe(fdpipe) < 0)
		return (-1);
	dup2(t_pipe->tmpout, 1);
	i = 0;
	while (cmds->delimiter[i + 1])
	{
		line = readline("heredoc> ");
		if (!line)
		{
			i++;
			continue ;
		}
		if (!ft_strncmp(line, cmds->delimiter[i], ft_strlen(line) + 1))
			i++;
		free(line);
	}
	line = readline("heredoc> ");
	if (!line)
		return (close(fdpipe[1]), fdpipe[0]);
	while (ft_strncmp(line, cmds->delimiter[i], ft_strlen(line) + 1))
	{
		ft_putstr_fd(line, fdpipe[1]);
		ft_putstr_fd("\n", fdpipe[1]);
		free(line);
		line = readline("heredoc> ");
		if (!line)
			break ;
	}
	return (close(fdpipe[1]), free(line), fdpipe[0]);
}

void	ft_error_127(char ***env, char ***var_export)
{
	ft_putstr_fd(": command no found\n", 2);
	ft_change_va_report(env, var_export, 127);
	exit(127);
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
	//int		lvl;

	//lvl = ft_atoi(search_env("SHLVL", *env));
	printf("argv %s\n", cmds->argv[0]);
	shell = search_path(*env, cmds->argv[0], 0);
	printf("argv %s\n", cmds->argv[0]);
	//shell = search_path(*env, cmds->argv[0], 0);
	if (exec_builtin(cmds->argv, env, var_export))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		if (!access(cmds->argv[0], F_OK))
			{
				free(shell);
				shell = ft_strdup(cmds->argv[0]);
			}
		// else if (shell == NULL && !access(*cmds->argv, F_OK))
		// {
		// 	shell = search_env("PWD", *env);
		// 	ft_export(ft_strjoin("SHLVL=", ft_itoa(++lvl)), env, var_export);
		// }
		else if (shell == NULL)
			ft_error_127(env, var_export);
		//free(shell);
		execve(shell, &cmds->argv[0], *env);
		perror("Error execve");
		exit(-1);
	}
	free(shell);
	return (pid);
}
