#include "../includes/minishell.h"

t_command	*parser(char *input)
{
	t_command	*b;
	int			n_cmds;
	char		**split_input;

	split_input = lexer(input);
	//comprobar la creacion del char** ha sido correcta
	n_cmds = count_cmds(split_input);
	b = ft_calloc(sizeof(t_command), (n_cmds + 1));
	last_cmd_table(b, n_cmds);
	if (!b)
		perror("Error");
	fill_cmds(b, split_input);
	return (b);
}

void	fill_cmds(t_command *b, char **split_input)
{
	// int	cmd;
	// int	pos;
	// int	j;
	// int	i;
	// int	redir;
	t_fill	var;

	var.cmd = 0;
	var.i = 0;
	while (split_input[var.i])
	{
		var.pos = var.i;
		var.redir = 0;
		while (split_input[var.i] && !ft_issame(split_input[var.i][0], "|"))
		{
			if (ft_issame(split_input[var.i][0], "<>"))
				var.redir = var.i;
			var.i++;
		}
		create_cmds(b, split_input, var);
		// b[cmd].argv = ft_calloc(sizeof(char *), i + 1);
		// j = 0;
		// while (pos < i)
		// 	b[cmd].argv[j++] = ft_strdup(split_input[pos++]);
		// cmd++;
		// if (split_input[i] && ft_issame(split_input[i][0], "|"))
		// 	i++;
	}
}

void	create_cmds(t_command *b, char	**split_input, t_fill var)
{
	int	a;

	a = 0;
	if (var.redir == 0)
		a = var.i;
	else
		a = var.redir;
	b[var.cmd].argv = ft_calloc(sizeof(char *), a + 1);
	var.j = 0;
	while (var.pos < var.i)
		b[var.cmd].argv[var.j++] = ft_strdup(split_input[var.pos++]);
	var.cmd++;
	if (split_input[var.i] && ft_issame(split_input[var.i][0], "|"))
		var.i++;
}

int	count_cmds(char **split_input)
{
	int	cmds;

	cmds = 1;
	while (*split_input)
	{
		if (*split_input[0] == '|')
			cmds++;
		split_input++;
	}
	return (cmds);
}

void	last_cmd_table(t_command *b, int n_cmds)
{
	b[n_cmds].argv = NULL;
	b[n_cmds].infile = NULL;
	b[n_cmds].outfile = NULL;
	b[n_cmds].last = 1;
}