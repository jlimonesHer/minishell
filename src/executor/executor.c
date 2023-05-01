/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriga <abarriga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:19:50 by jlimones          #+#    #+#             */
/*   Updated: 2023/05/01 14:45:52 by abarriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	condition_fd(t_command *cmds, t_fd_pipes *t_pipe, int *fds, int i)
{
	if (cmds[i].delimiter)
		t_pipe->fdin = is_delim(&cmds[i], t_pipe);
	dup2(t_pipe->fdin, 0);
	close(t_pipe->fdin);
	if (i != cmds->n_cmds - 1)
	{
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
}

void	kill_child(int n_cmds, int *children)
{
	int	i;

	i = 0;
	while (i < n_cmds -1)
	{
		readline("");
		kill(children[i], SIGKILL);
		i++;
	}
}

static void	loop_cmds(t_command *cmds, t_fd_pipes *t_pipe, char ***env,
	char ***va_export)
{
	int	i;
	int	pid;
	int	status;
	int	fds[2];
	int	*children;

	i = -1;
	children = ft_calloc(sizeof(int), cmds->n_cmds);
	while (++i < cmds->n_cmds)
	{
		if (pipe(fds) < 0)
			return (perror("Error: pipe: "));
		condition_fd(cmds, t_pipe, fds, i);
		dup2(t_pipe->fdout, 1);
		close(t_pipe->fdout);
		pid = ft_create_child(&cmds[i], env, va_export);
		children[i] = pid;
		if (i == cmds->n_cmds - 1)
		{
			waitpid(pid, &status, 0);
			kill_child(cmds->n_cmds, children);
			free(children);
		}
		ft_change_va_report(env, va_export, WEXITSTATUS(status));
	}
}

void	executor(t_command *cmds, char ***env, char ***var_export)
{
	t_fd_pipes	*t_pipe;

	t_pipe = ft_calloc(sizeof(t_fd_pipes), 2);
	t_pipe->tmpin = dup(0);
	t_pipe->tmpout = dup(1);
	if (cmds->n_cmds && cmds->fd_in)
		t_pipe->fdin = cmds->fd_in;
	else
		t_pipe->fdin = dup(0);
	loop_cmds(cmds, t_pipe, env, var_export);
	dup2(t_pipe->tmpin, 0);
	dup2(t_pipe->tmpout, 1);
	close(t_pipe->tmpin);
	close(t_pipe->tmpout);
	free(t_pipe);
}

int	ft_create_child(t_command *cmds, char ***env, char ***var_export)
{
	int		pid;
	char	*shell;

	shell = search_path(*env, cmds->argv[0], 0);
	printf("shell = %p\n", shell);
	if (exec_builtin(cmds->argv, env, var_export))
		return (free(shell), -1);
	pid = fork();
	if (pid == 0)
	{
		ft_child_routine(cmds, shell, env, var_export);
	}
	free(shell);
	return (pid);
}
