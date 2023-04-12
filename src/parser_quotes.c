#include "../includes/minishell.h"

void	expand(t_command *b, char **envp)
{
	t_expand	e;

	e.i = 0;
	while (b->last != 1)
	{
		while (b->argv[e.i])
		{
			if (ft_issame(b->argv[e.i][0], "\""))
				b->argv[e.i] = expand_quotes(&b->argv[e.i][1], envp);
			else if (ft_issame(b->argv[e.i][0], "\'"))
				b->argv[e.i] = remove_quote(b->argv[e.i]);
			else
				b->argv[e.i] = expand_text(b->argv[e.i], envp);
			e.i++;
		}
		b++;
	}
}


// char	*remove_quote()
// {

// }

char	*expand_text(char *cmd, char **envp)
{
	// t_expand	e;
	// printf("comando:%s\n", cmd);
	if (cmd[0] == '$')
		cmd = search_env(&cmd[1], envp);
	// printf("este es el env %s\n", e.env);
	return (cmd);
}

char	*expand_quotes(char *cmd, char **envp)
{
	t_expand	e;

	e.j = 0;
	while (cmd[e.j])
	{
		if (cmd[e.j] == '$')
		{
			e.bg = e.j;
			while (!ft_issame(cmd[e.j], " \"><|\t\v\n\0"))
				e.j++;
			e.var = ft_calloc(e.j - e.bg, sizeof(char));
			ft_strlcpy(e.var, &cmd[e.bg + 1], e.j - e.bg);
			e.env = search_env(e.var, envp);
			e.sub = ft_substr(cmd, 0, e.bg);
			e.line = ft_strjoin(e.sub, e.env);
			e.join = ft_strjoin(e.line, &cmd[e.j]);
			e.j = (ft_strlen(e.env) - ft_strlen(e.var) + 1);
			cmd = e.join;
			free_quotes(&e);
		}
		e.j++;
	}
	e.join[ft_strlen(e.join) - 1] = '\0';
	return (e.join);
}

void	free_quotes(t_expand *e)
{
	free(e->var);
	free(e->env);
	free(e->line);
	free(e->sub);
}

char	*search_env(char *var, char **envp)
{
	int		len;
	int		len_str;
	int		i;
	char	*str;

	i = 0;
	str = ft_strjoin(var, "=");
	len = ft_strlen(str);
	while (ft_strnstr(envp[i], str, len) == 0)
		i++;
	if (!envp[i + 1])
		perror("ERROR var envp");
	len_str = ft_strlen(envp[i]);
	var = ft_substr(envp[i], len, (len_str - len));
	return (var);
}

// void	expand_quotes(t_command *b)
// {
// 	t_expand	e;

// 	e.i = 0;
// 	while (b->last != 1)
// 	{
// 		while (b->argv[e.i])
// 		{
// 			e.j = 0;
// 			if (!ft_issame(b->argv[e.i][0], "\'"))
// 			{
// 				while (b->argv[e.i][e.j])
// 				{
// 					if (b->argv[e.i][e.j] == '$')
// 					{
// 						e.bg = e.j;
// 						while (!ft_issame(b->argv[e.i][e.j], " \""))
// 							e.j++;
// 						e.var = ft_calloc(e.j - e.bg, sizeof(char));
// 						ft_strlcpy(e.var, &b->argv[e.i][e.bg + 1], e.j - (e.bg));
// 						printf("Esta la variable de entorno:%s\n", e.var);
// 					}
// 					e.j++;
// 				}
// 			}
// 			e.i++;
// 		}
// 		b++;
// 	}
// }

// void	expand_quotes(t_command *b)
// {
// 	t_expand	e;

// 	e.i = 0;
// 	while (b->last != 1)
// 	{
// 		while (b->argv[e.i])
// 		{
// 			e.j = 0;
// 			if (!ft_issame(b->argv[e.i][0], "\'"))
// 			{
// 				while (b->argv[e.i][e.j])
// 				{
// 					if (b->argv[e.i][e.j] == '$')
// 					{
// 						e.bg = e.j;
// 						while (!ft_issame(b->argv[e.i][e.j], " \""))
// 							e.j++;
// 						e.var = ft_calloc(e.j - e.bg + 1, sizeof(char));
// 						ft_strlcpy(e.var, &b->argv[e.i][e.bg + 1], e.j - e.bg);
// 						printf("Esta la variable de entorno:%s\n", e.var);
// 					}
// 					e.j++;
// 				}
// 			}
// 			e.i++;
// 		}
// 		b++;
// 	}
// }