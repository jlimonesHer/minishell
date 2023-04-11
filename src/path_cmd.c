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

/**
 * @brief 
 * 
 * @param cmds struct donde se guardan los comandos
 * @param env variables de entorno
 * @param i indice de comando
 * @return int pid de hijo creado
 */
static int	ft_create_child(t_command *cmds, char **env, int i)
{
	int		pid;
	char	*shell;

	if (exec_builtin(cmds->argv, env))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		shell = search_path(env, *cmds[i].argv);
		if (shell == NULL)
		{
			ft_putstr_fd(": command no found\n", 2);
			exit(-1);
		}
		execve(shell, &cmds[i].argv[0], env);
		perror("Error: ");
		exit(-1);
	}
	return (pid);
}

void	ft_one_cmd(t_command *cmds, char **env)
{
	int			i;
	int			pid;
	int			status;
	int			fds[2];
	t_fd_pipes	*t_pipe;

	t_pipe = malloc(sizeof(t_fd_pipes));
	i = -1;
	t_pipe->fdin = dup(0);
	t_pipe->tmpin = dup(0);
	t_pipe->tmpout = dup(1);
	while (++i < cmds->n_cmds)
	{
		dup2(t_pipe->fdin, 0);
		close(t_pipe->fdin);
		if (i != cmds->n_cmds - 1)
		{
			pipe(fds); //controlar errores
			t_pipe->fdout = fds[1];
			t_pipe->fdin = fds[0];
		}
		else
			t_pipe->fdout = dup(t_pipe->tmpout);
		dup2(t_pipe->fdout, 1);
		close(t_pipe->fdout);
		pid = ft_create_child(cmds, env, i);
		printf("%i\n", i);
		printf("%i\n", cmds->n_cmds);
		if (i == cmds->n_cmds - 1)
			waitpid(pid, &status, 0);
	}
	dup2(t_pipe->tmpin, 0);
	dup2(t_pipe->tmpout, 1);
	close(t_pipe->tmpin);
	close(t_pipe->tmpout);
}
