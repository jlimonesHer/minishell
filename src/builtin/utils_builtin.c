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
	return (env_cp);
}

static	void	ft_error_export(char *argv)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

char	**add_export(char **envp, char *var_export)
{
	char	**env_cp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env_cp = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (envp[++i])
		env_cp[i] = ft_strdup(envp[i]);
	envp[i] = var_export;
	return (env_cp);
}

int	ft_export(char *argv, char **envp, char **var_export)
{
	int		i;
	char	key[100];

	i = -1;
	if (!argv)
		return (printf("solo 1\n"), 0);
	while (argv[++i] && (ft_isalnum(argv[i]) || ft_issame(argv[i], "?_"))
		&& argv[i] != '=')
		key[i] = argv[i];
	key[i] = '\0';
	if (argv[i] != '=')
		ft_error_export(argv);
	else
		printf("%s\n", envp[0]);
	env_copy(envp);
	return (0);
}
