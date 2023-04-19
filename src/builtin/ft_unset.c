#include "../../includes/minishell.h"

void	get_va_env(char *key, char *argv, char ***envp)
{
	int	i;
	char **env = *envp;
	
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], argv, ft_strlen(argv)))
			i++;
		else
			break ;
	}
	if (env[i] == NULL)
	{
		free(env[i]);
		add_export(envp, key);
	}
	else if (!ft_strncmp(env[i], argv, ft_strlen(argv)))
	{
		free(env[i]);
		env[i] = ft_strdup(key);
	}
}

char	**ft_unset(char *argv, char ***env)
{
	char	**env_cp;
	int		i;

	i = 0;
	while (env[i])
		i++;
	env_cp = ft_calloc(sizeof(char *), (i + 1));
	i = -1;
	while ((*env)[++i])
	{
		if (ft_strncmp(argv, (*env)[i], ft_strlen(argv)))
			env_cp[i] = ft_strdup((*env)[i]);
	}
	i = -1;
	// while ((*env)[++i])
	// 	free((*env)[i]);
	//env_cp[i] = NULL;
	return (env_cp);
}
