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
		var.redir_in = -1;
		var.redir = -1;
		while (split_input[var.i] && !ft_issame(split_input[var.i][0], "|"))
		{
			if (ft_issame(split_input[var.i][0], "<"))
				var.redir_in = var.i;
			if (ft_issame(split_input[var.i][0], ">"))
				var.redir = var.i;
			var.i++;
		}
		create_cmds(b, split_input, &var);
		// take_fd();
		// expand_quotes();

		// b[cmd].argv = ft_calloc(sizeof(char *), i + 1);
		// j = 0;
		// while (pos < i)
		// 	b[cmd].argv[j++] = ft_strdup(split_input[pos++]);
		// cmd++;
		// if (split_input[i] && ft_issame(split_input[i][0], "|"))
		// 	i++;
	}
}

void	create_cmds(t_command *b, char	**split_input, t_fill *var)
{
	int	a;

	a = 0;
	printf("este es el redir_in:%d\n", var->redir_in);
	if (var->redir_in != -1)
	{
		a -= 2;
		b[var->cmd].infile = split_input[var->redir_in + 1];
		// REVISAR SI TENGO QUE RESERVAR MEMORIA
	}
	printf("este es el archivo infile:%s\n", b[var->cmd].infile);
	if (var->redir == -1)
		a = var->i;
	else
		a = var->redir;
	
	printf("este es la pos de la redir de salida: %d\n", var->redir);
	b[var->cmd].argv = ft_calloc(sizeof(char *), a + 1);
	var->j = 0;
	while (var->pos < a)
		b[var->cmd].argv[var->j++] = ft_strdup(split_input[var->pos++]);
	var->cmd++;
	if (split_input[var->i] && ft_issame(split_input[var->i][0], "|"))
		var->i++;
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