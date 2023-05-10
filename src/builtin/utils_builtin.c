/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlimones <jlimones@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:19:27 by jlimones          #+#    #+#             */
/*   Updated: 2023/05/10 10:33:08 by jlimones         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	ft_putendl_fd(buffer, 1);
	free(buffer);
}

char	**env_copy1(char **env)
{
	char	**env_cp;
	int		i;

	i = 0;
	while (env[i])
		i++;
	env_cp = ft_calloc(sizeof(char *), (i + 1));
	i = 0;
	while (env[i])
	{
		env_cp[i] = ft_strdup(env[i]);
		i++;
	}
	ft_freewords(-1, env);
	return (env_cp);
}

/**
 * @brief 
 * 
 * @param env 
 * @return char** 
 */
char	**env_copy2(char **env)
{
	char	**env_cp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	env_cp = ft_calloc(sizeof(char *), (i + 2));
	env_cp[0] = ft_strdup("?=0");
	i = 1;
	while (env[j])
	{
		env_cp[i] = ft_strdup(env[j]);
		j++;
		i++;
	}
	return (env_cp);
}

void	add_export(char ***envp, char *argv)
{
	char	**env_cp;
	int		i;

	i = 0;
	while ((*envp)[i])
		i++;
	env_cp = ft_calloc(sizeof(char *), (i + 2));
	i = -1;
	while ((*envp)[++i])
			env_cp[i] = ft_strdup((*envp)[i]);
	env_cp[i] = ft_strdup(argv);
	i++;
	i = -1;
	ft_freewords(-1, *envp);
	*envp = env_cp;
}

void	ft_export(char *argv, char ***envp, char ***var_export)
{
	int		i;
	char	*argv_cp;

	i = 0;
	if (!argv)
		return (ft_env(*var_export));
	while (argv[i] && (ft_isalnum(argv[i]) || ft_issame(argv[i], "?_"))
		&& argv[i] != '=')
		i++;
	argv_cp = ft_calloc(sizeof(char), i + 1);
	i = -1;
	while (argv[++i] && (ft_isalnum(argv[i]) || ft_issame(argv[i], "?_"))
		&& argv[i] != '=')
		argv_cp[i] = argv[i];
	if (argv[i] == '=')
	{		
		get_va_env(argv, argv_cp, envp);
		get_va_env(argv, argv_cp, var_export);
	}
	else
		add_export(var_export, argv);
	free(argv_cp);
}
