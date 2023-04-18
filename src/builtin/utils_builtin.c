#include "../../includes/minishell.h"

char	**env_copy(char **env)
{
	char	**env_cp;
	int		i;

	i = 0;
	while (env[i])
		i++;
	env_cp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		env_cp[i] = ft_strdup(env[i]);
	env_cp[i] = NULL;
	return (env_cp);
}

// static	void	ft_error_export(char *argv)
// {
// 	ft_putstr_fd("export: ", 2);
// 	ft_putstr_fd(argv, 2);
// 	ft_putstr_fd(": not a valid identifier\n", 2);
// }

char	**add_export(char ***envp, char *var_export)
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
	env_cp[i] = var_export;
	i++;
	env_cp[i] = NULL;
	i = -1;
	while ((*envp)[++i])
		free((*envp)[i]);
	free(*envp);
	return (env_cp);
}

void	ft_export(char *argv, char ***envp, char ***var_export)
{
	int		i;

	i = -1;
	if (!argv)
		return (ft_env(*var_export));
	while (argv[++i] && (ft_isalnum(argv[i]) || ft_issame(argv[i], "?_"))
		&& argv[i] != '=')
		i++;
	if (argv[i] && argv[i] == '=')
		*envp = add_export(envp, argv);
	*var_export = add_export(var_export, argv);
}
