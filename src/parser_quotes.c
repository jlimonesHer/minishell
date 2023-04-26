#include "../includes/minishell.h"

void	expand(t_command *b, char **envp)
{
	t_expand	e;

	while (b->last != 1)
	{
		e.i = -1;
		while (b->argv && b->argv[++e.i])
		{
			if (ft_issame(b->argv[e.i][0], "\""))
				b->argv[e.i] = expand_quotes(&b->argv[e.i][1], envp);
			else if (ft_issame(b->argv[e.i][0], "\'"))
				b->argv[e.i] = remove_quote(&b->argv[e.i][1]);
			else
				b->argv[e.i] = expand_text(b->argv[e.i], envp);
		printf("i: %d\n", e.i);
		printf("Imprime last\n");
		}
		b++;
		printf("last: %d\n", b->last);
	}
	printf("ACABA\n");
}

char	*remove_quote(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	cmd[len - 1] = '\0';
	return (cmd);
}

char	*expand_text(char *cmd, char **envp)
{
	if (cmd[0] == '$')
	{
		cmd = search_env(&cmd[1], envp);
		if (cmd == NULL)
			return (NULL);
	}
	printf("cmd: %s\n", cmd);
	return (cmd);
}

char	*expand_quotes(char *cmd, char **envp)
{
	t_expand	e;

	e.j = -1;
	e.join = NULL;
	while (cmd[++(e.j)])
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
	}
	if (e.join == NULL)
		e.join = ft_strdup(cmd);
	return (e.join[ft_strlen(e.join) - 1] = '\0', e.join);
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
	{
		if (!envp[i + 1])
			return (ft_strdup(""));
		i++;
	}
	len_str = ft_strlen(envp[i]);
	var = ft_substr(envp[i], len, (len_str - len));
	return (var);
}
