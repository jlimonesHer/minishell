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

// void	fill_cmds(t_command *b, char **split_input)
// {
// 	t_fill	var;

// 	var.cmd = 0;
// 	var.i = 0;
// 	while (split_input[var.i])
// 	{
// 		var.pos = var.i;
// 		var.redir_in = -1;
// 		var.redir_out = -1;
// 		while (split_input[var.i] && !ft_issame(split_input[var.i][0], "|"))
// 		{
// 			if (ft_issame(split_input[var.i][0], "<"))
// 				var.redir_in = var.i;
// 			if (ft_issame(split_input[var.i][0], ">"))
// 			{
// 				var.redir_out = var.i;
// 				if (split_input[var.i][1])
// 					b[var.cmd].double_out = 1;
// 			}
// 			var.i++;
// 		}
// 		create_cmds(b, split_input, &var);
// 	}
// 	take_fd(b);
// 	expand_quotes(b);
// }

void	fill_cmds(t_command *b, char **split_input)
{
	t_fill	var;

	var.cmd = 0;
	var.i = 0;
	while (split_input[var.i])
	{
		var.pos = var.i;
		var.redir_in = -1;
		var.redir_out = -1;
		var.num_r_in = 0;
		count_redir(split_input, &var, b);
		while (split_input[var.i] && !ft_issame(split_input[var.i][0], "|"))
		{
			if (ft_issame(split_input[var.i][0], "<"))
				create_infile(b, split_input, &var);
			else if (ft_issame(split_input[var.i][0], ">"))
				create_outfile(b, split_input, &var);
			else
				create_cmd(b, split_input, &var);
			// var.i++;
		}
		create_cmds(b, split_input, &var);
	}
	take_fd(b);
	expand_quotes(b);
}

void	count_redir(char	**split_input, t_fill *var, t_command *b)
{
	int	i;

	i = 0;
	var->c_in = 0;
	var->c_out = 0;
	while (split_input[i] && !ft_issame(split_input[i][0], "|"))
	{
		if (ft_issame(split_input[i][0], "<"))
			var->c_in += 1;
		else if (ft_issame(split_input[i][0], ">"))
			var->c_out += 1;
	}
	if (var->c_in > 0)
		b[var->cmd].infile = ft_calloc(var->c_in + 1, sizeof(char *));
	if (var->c_out > 0)
	{
		b[var->cmd].outfile = ft_calloc(var->c_out + 1, sizeof(char *));
		b[var->cmd].double_out = ft_calloc(var->c_out + 1, sizeof(int));
	}
	b[var->cmd].argv = ft_calloc(sizeof(char *),
			i - (2 * (var->c_in + var->c_out)) + 1);
}

void	create_infile(t_command *b, char **split_input, t_fill *var)
{
	b[var->cmd].infile[var->num_r_in] = split_input[var->i + 1];
	var->num_r_in += 1;
}

void	create_outfile(t_command *b, char **split_input, t_fill *var)
{
	b[var->cmd].outfile[var->num_r_out] = split_input[var->i + 1];
	if (split_input[var->i][1])
		b[var->cmd].double_out[var->num_r_out] = 1;
	else
		b[var->cmd].double_out[var->num_r_out] = 0;
	var->num_r_out += 1;
}

void	create_cmds(t_command *b, char	**split_input, t_fill *var)
{
	var->a = 0;
	if (var->redir_in != -1)
	{
		var->a -= 2;
		var->pos += 2;
		b[var->cmd].infile = split_input[var->redir_in + 1];
	}
	if (var->redir_out != -1)
	{
		var->final = var->redir_out;
		var->a += var->redir_out;
		b[var->cmd].outfile = split_input[var->redir_out + 1];
	}
	else
	{
		var->a += var->i;
		var->final = var->i;
	}
	b[var->cmd].argv = ft_calloc(sizeof(char *), var->a + 1);
	var->j = 0;
	while (var->pos < var->final)
		b[var->cmd].argv[var->j++] = ft_strdup(split_input[var->pos++]);
	var->cmd++;
	if (split_input[var->i] && ft_issame(split_input[var->i][0], "|"))
		var->i++;
}

void	expand_quotes(t_command *b)
{
	t_expand	e;

	e.i = 0;
	while (b->last != 1)
	{
		while (b->argv[e.i])
		{
			e.j = 0;
			if (!ft_issame(b->argv[e.i][0], "\'"))
			{
				while (b->argv[e.i][e.j])
				{
					if (b->argv[e.i][e.j] == '$')
					{
						e.bg = e.j;
						while (!ft_issame(b->argv[e.i][e.j], " \""))
							e.j++;
						e.var = ft_calloc(e.j - e.bg + 1, sizeof(char));
						ft_strlcpy(e.var, &b->argv[e.i][e.bg + 1], e.j - e.bg);
						printf("Esta la variable de entorno:%s\n", e.var);
					}
					e.j++;
				}
			}
			e.i++;
		}
		b++;
	}
}

void	take_fd(t_command *b)
{
	while (b->last != 1)
	{
		if (b->infile != NULL)
		{
			b->fd_in = open(b->infile, O_RDONLY);
		}
		if (b->outfile != NULL)
		{
			if (b->double_out == 0)
			b->fd_out = open(b->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (b->double_out == 1)
			b->fd_out = open(b->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		printf("este es el fd de entrada: %d\n", b->fd_in);
		printf("este es el fd de salida: %d\n", b->fd_out);
		b++;
	}
}

// void	create_cmds(t_command *b, char	**split_input, t_fill *var)
// {
// 	var->a = 0;
// 	printf("este es la pos redir_in:%d\n", var->redir_in);
// 	if (var->redir_in != -1)
// 	{
// 		var->a -= 2;
// 		var->pos += 2;
// 		b[var->cmd].infile = split_input[var->redir_in + 1];
// 		// REVISAR SI TENGO QUE RESERVAR MEMORIA
// 	}
// 	printf("este es el archivo infile:%s\n", b[var->cmd].infile);
// 	if (var->redir_out != -1)
// 	{
// 		var->final = var->redir_out;
// 		var->a += var->redir_out;
// 		b[var->cmd].outfile = split_input[var->redir_out + 1];
// 	}
// 	else
// 	{
// 		var->a += var->i;
// 		var->final = var->i;
// 	}
// 	printf("este es la pos de la redir_out: %d\n", var->redir_out);
// 	printf("este es el archivo outfile:%s\n", b[var->cmd].outfile);
// 	printf("este es el append double:%i\n", b[var->cmd].double_out);
// 	b[var->cmd].argv = ft_calloc(sizeof(char *), var->a + 1);
// 	var->j = 0;
// 	while (var->pos < var->final)
// 		b[var->cmd].argv[var->j++] = ft_strdup(split_input[var->pos++]);
// 	var->cmd++;
// 	if (split_input[var->i] && ft_issame(split_input[var->i][0], "|"))
// 		var->i++;
// }

// void	create_cmds(t_command *b, char	**split_input, t_fill *var)
// {
// 	var->a = 0;
// 	if (var->redir_in != -1)
// 	{
// 		var->a -= 2;
// 		var->pos += 2;
// 		b[var->cmd].infile = split_input[var->redir_in + 1];
// 	}
// 	if (var->redir_out != -1)
// 	{
// 		var->final = var->redir_out;
// 		var->a += var->redir_out;
// 		b[var->cmd].outfile = split_input[var->redir_out + 1];
// 	}
// 	else
// 	{
// 		var->a += var->i;
// 		var->final = var->i;
// 	}
// 	b[var->cmd].argv = ft_calloc(sizeof(char *), var->a + 1);
// 	var->j = 0;
// 	while (var->pos < var->final)
// 		b[var->cmd].argv[var->j++] = ft_strdup(split_input[var->pos++]);
// 	var->cmd++;
// 	if (split_input[var->i] && ft_issame(split_input[var->i][0], "|"))
// 		var->i++;
// }

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