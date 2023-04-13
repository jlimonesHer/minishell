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

static	void ft_error_export(char *argv)
{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
}

void	ft_export(char *argv, char **env)
{
	int		i;
	char	key[100];

	i = -1;
	while (argv[++i] && (ft_isalnum(argv[i]) || ft_issame(argv[i], "?_"))
		&& argv[i] != '=')
		key[i] = argv[i];
	key[i] = '\0';
	if (argv[i] != '=')
		ft_error_export(argv);
	else
		printf("%s\n", env[0]);
	env_copy(env);
}