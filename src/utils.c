#include "../includes/minishell.h"

void	free_quotes(t_expand *e)
{
	free(e->var);
	free(e->env);
	free(e->line);
	free(e->sub);
	e->var = NULL;
	e->env = NULL;
	e->line = NULL;
	e->sub = NULL;
}

void	free_first_quotes(t_expand *e)
{
	free(e->var);
	free(e->env);
	e->var = NULL;
	e->env = NULL;
}

void	ft_change_va_report(char ***env, char ***va_export, int b)
{
	char	*b2;
	char	*itoa;

	itoa = ft_itoa(b);
	b2 = ft_strjoin("?=", itoa);
	free(itoa);
	free((*env)[0]);
	(*env)[0] = ft_strdup(b2);
	free((*va_export)[0]);
	(*va_export)[0] = ft_strdup(b2);
	free(b2);
}

void	ft_ispipe(char	**split_input, int *i, int *cmd)
{
	if (split_input[*i] && (ft_issame(split_input[*i][0], "|")))
	{
		*i += 1;
		*cmd += 1;
	}
}
