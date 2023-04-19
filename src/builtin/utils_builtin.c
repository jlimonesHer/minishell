#include "../../includes/minishell.h"

char	**env_copy(char **env)
{
	char	**env_cp;
	int		i;

	i = 0;
	while (env[i])
	{
		//printf("env[%d]: %s\n", i, env[i]);
		i++;
	}
	env_cp = ft_calloc(sizeof(char *), (i + 1));
	i = 0;
	while (env[i])
	{
		env_cp[i] = ft_strdup(env[i]);
		i++;
	}
	env_cp[i] = NULL;
	return (env_cp);
}

// static	void	ft_error_export(char *argv)
// {
// 	ft_putstr_fd("export: ", 2);
// 	ft_putstr_fd(argv, 2);
// 	ft_putstr_fd(": not a valid identifier\n", 2);
// }

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
	env_cp[i] = argv;
	i++;
	//env_cp[i] = NULL;
	i = -1;
	while ((*envp)[++i])
		free((*envp)[i]);
	free(*envp);
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
}
