/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlimones <jlimones@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:20:20 by jlimones          #+#    #+#             */
/*   Updated: 2023/04/29 16:55:16 by jlimones         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	while (*env && !ft_strnstr(*env, "PATH=", 5))
		env++;
	substr_f = ft_substr(*env, 5, ft_strlen(*env) - 5);
	paths = ft_split(substr_f, ':');
	free(substr_f);
	substr = ft_strjoin("/", cmd);
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

void	ft_loop_delim(int fdpipe[2], t_command *cmds, int i, char *line)
{
	while (ft_strncmp(line, cmds->delimiter[i], ft_strlen(line) + 1))
	{
		ft_putstr_fd(line, fdpipe[1]);
		ft_putstr_fd("\n", fdpipe[1]);
		free(line);
		line = readline("heredoc> ");
		if (!line)
			break ;
	}
	free(line);
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
	ft_loop_delim(fdpipe, cmds, i, line);
	return (close(fdpipe[1]), fdpipe[0]);
}

void	ft_error_127(char ***env, char ***var_export, char	**cmds)
{
	ft_putstr_fd(ft_strjoin(cmds[0], ": command no found\n"), 2);
	ft_change_va_report(env, var_export, 127);
	exit(127);
}

void	ft_child_routine(t_command *cmds, char *shell,
	char ***env, char ***var_export)
{
	int		lvl;
	char	*num;
	char	*tmp;

	tmp = search_env("SHLVL", *env);
	lvl = ft_atoi(tmp);
	free(tmp);
	if (!access(cmds->argv[0], F_OK))
	{
		free(shell);
		num = ft_itoa(++lvl);
		ft_export(ft_strjoin("SHLVL=", num), env, var_export);
		free(num);
		shell = ft_strdup(cmds->argv[0]);
	}
	else if (shell == NULL)
		ft_error_127(env, var_export, &cmds->argv[0]);
	execve(shell, &cmds->argv[0], *env);
	perror("Error execve");
	exit(-1);
}
