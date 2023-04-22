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

/**
 * @brief 
 * 
 * @param cmds struct donde se guardan los comandos
 * @param env variables de entorno
 * @param i indice de comando
 * @return int pid de hijo creado
 */
static int	ft_create_child(t_command *cmds, char ***env, char ***var_export)
{
	int		pid;
	char	*shell;

	if (exec_builtin(cmds->argv, env, var_export))
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		shell = search_path(*env, cmds->argv[0]);
		if (shell == NULL)
		{
			ft_putstr_fd(": command no found\n", 2);
			exit(-1);
		}
		execve(shell, &cmds->argv[0], *env);
	}
	return (pid);
}

/**
 * @brief loop creado para partir la funcion executor descrita debajo
 * 
 * @param cmds estructura de datos
 * @param t_pipe estructura de fds
 * @param env variables globales
 */
static void	loop_cmds(t_command *cmds, t_fd_pipes *t_pipe, char ***env,
	char ***va_export)
{
	int	i;
	int	pid;
	int	status;
	int	fds[2];

	i = -1;
	while (++i < cmds->n_cmds)
	{
		dup2(t_pipe->fdin, 0);
		close(t_pipe->fdin);
		if (i != cmds->n_cmds - 1)
		{
			if (pipe(fds) == -1)
				return (perror("Error:"));
			t_pipe->fdout = fds[1];
			t_pipe->fdin = fds[0];
		}
		else
		{
			if (cmds[i].fd_out)
				t_pipe->fdout = cmds[i].fd_out;
			else
				t_pipe->fdout = dup(t_pipe->tmpout);
		}
		dup2(t_pipe->fdout, 1);
		close(t_pipe->fdout);
		pid = ft_create_child(&cmds[i], env, va_export);
		if (i == cmds->n_cmds - 1)
			waitpid(pid, &status, 0);
		ft_change_va_report(env, va_export, WEXITSTATUS(status));
	}
}

/**
 * @brief funcion para crear los procesos necesarios para ejecutar los comandos
 * introducidos
 * 
 * @param cmds estructura de datos
 * @param env variables globales
 */
void	executor(t_command *cmds, char ***env, char ***var_export)
{
	t_fd_pipes	*t_pipe;

	t_pipe = ft_calloc(sizeof(t_fd_pipes), 2);
	if (cmds->n_cmds && cmds->fd_in)
		t_pipe->fdin = cmds->fd_in;
	else
		t_pipe->fdin = dup(0);
	t_pipe->tmpin = dup(0);
	t_pipe->tmpout = dup(1);
	loop_cmds(cmds, t_pipe, env, var_export);
	dup2(t_pipe->tmpin, 0);
	dup2(t_pipe->tmpout, 1);
	close(t_pipe->tmpin);
	close(t_pipe->tmpout);
	free(t_pipe);
}
