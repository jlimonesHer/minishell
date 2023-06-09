/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlimones <jlimones@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:19:56 by jlimones          #+#    #+#             */
/*   Updated: 2023/05/10 15:58:04 by jlimones         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **argv)
{
	int		i;
	int		j;
	int		new_line;

	new_line = 1;
	i = -1;
	j = 0;
	if (!argv[1])
		return ((void)printf("\n"));
	if (!ft_strncmp(argv[1], "-n", 2))
	{
		new_line = 0;
		j++;
	}
	while (argv[++j])
	{
		while (argv[j][++i])
			printf("%c", argv[j][i]);
		printf(" ");
		i = -1;
	}
	if (new_line)
		printf("\n");
}

static void	path_pwd_old(char *path, char ***env)
{
	int	i;
	int	j;

	i = 0;
	while ((*env)[i] && ft_strncmp((*env)[i], "PWD=", 4))
		i++;
	j = 0;
	while ((*env)[j] && ft_strncmp((*env)[j], "OLDPWD=", 7))
		j++;
	free((*env)[j]);
	(*env)[j] = ft_strjoin("OLDPWD=", getenv("PWD"));
	free((*env)[i]);
	(*env)[i] = ft_strjoin("PWD=", path);
}

void	ft_free_paths(char *path, char *path2)
{
	free(path2);
	free(path);
}

static	void	ft_cd(char **argv, char ***env, char ***va_export)
{
	char	buffer[256];
	char	*path;
	char	*path2;

	getcwd(buffer, 256);
	if (!argv[1])
	{
		chdir(getenv("HOME"));
		return ;
	}
	if (argv[1][0] == '-')
	{
		chdir(search_env("OLDPWD", *env));
		return ;
	}
	path2 = ft_strjoin(buffer, "/");
	path = ft_strjoin(path2, argv[1]);
	if (chdir(argv[1]) < 0)
		ft_putstr_fd(("cd: no such file or directory: \n"), 2);
	else
	{	
		path_pwd_old(path, env);
		path_pwd_old(path, va_export);
	}
	ft_free_paths(path, path2);
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
		ft_cd(argv, envp, var_export);
	else if (!ft_strncmp(argv[0], "export", 7))
		ft_export(argv[1], envp, var_export);
	else if (!ft_strncmp(argv[0], "unset", 6))
		*envp = ft_unset(argv[1], envp);
	else if (!ft_strncmp(argv[0], "env", 4))
		ft_env(*envp);
	else if (!ft_strncmp(argv[0], "exit", 5))
	{
		ft_putstr_fd("exit\n", 1);
		if (argv[1])
			exit(ft_atoi(argv[1]));
		exit(0);
	}
	else
		is_build = 0;
	return (is_build);
}
