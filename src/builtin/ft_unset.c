#include "../../includes/minishell.h"

void	get_va_env(char *key, char *argv, char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], argv, ft_strlen(argv)))
			i++;
		else
			break ;
	}
	if ((*env)[i] == NULL)
	{
		free((*env)[i]);
		add_export(env, key);
	}
	else if (!ft_strncmp((*env)[i], argv, ft_strlen(argv)))
	{
		free((*env)[i]);
		(*env)[i] = ft_strdup(key);
	}
}

static int	search_key_env(char *argv, char ***env)
{
	int		i;
	int		t_f;

	t_f = 0;
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp(argv, (*env)[i], ft_strlen(argv)))
			t_f = 1;
		i++;
	}
	return (t_f);
}

char	**ft_unset(char *argv, char ***env)
{
	char	**env_cp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!search_key_env(argv, env))
		return (*env);
	while ((*env)[i])
		i++;
	env_cp = ft_calloc(sizeof(char *), (i));
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp(argv, (*env)[i], ft_strlen(argv)))
		{
			env_cp[j] = ft_strdup((*env)[i]);
			j++;
		}
		i++;
	}
	return (env_cp);
}

void	ft_env(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}
