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
	t_fill	var;

	var.cmd = 0;
	var.i = 0;
	while (split_input[var.i])
	{
		var.j = 0;
		var.num_r_in = 0;
		var.num_r_out = 0;
		count_redir(split_input, &var, b);
		while (split_input[var.i] && !ft_issame(split_input[var.i][0], "|"))
		{
			if (ft_issame(split_input[var.i][0], "<"))
				create_infile(b, split_input, &var);
			else if (ft_issame(split_input[var.i][0], ">"))
				create_outfile(b, split_input, &var);
			else
				create_cmd(b, split_input, &var);
		}
		if (split_input[var.i] && ft_issame(split_input[var.i][0], "|"))
		{
			var.i++;
			var.cmd++;
		}
	}
	// take_fd(b);
	// expand_quotes(b);
}

void	create_cmd(t_command *b, char	**split_input, t_fill *var)
{
	b[var->cmd].argv[var->j++] = ft_strdup(split_input[var->i++]);
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
		i++;
	}
	printf("este es el valor de redir de out:%d\n", var->c_out);
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
	printf("este es el infile %s\n", b[var->cmd].infile[var->num_r_in]);
	var->num_r_in += 1;
	var->i += 2;
}

void	create_outfile(t_command *b, char **split_input, t_fill *var)
{
	b[var->cmd].outfile[var->num_r_out] = split_input[var->i + 1];
	printf("este es el outfile %s\n", b[var->cmd].outfile[var->num_r_out]);
	if (split_input[var->i][1])
		b[var->cmd].double_out[var->num_r_out] = 1;
	else
		b[var->cmd].double_out[var->num_r_out] = 0;
	var->num_r_out += 1;
	var->i += 2;
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

// void	take_fd(t_command *b)
// {
// 	int	i;

// 	b->fd_in = -10;
// 	b->fd_out = -10;
// 	// printf("AQUI\n");
// 	while (b->last != 1)
// 	{
// 		i = 0;
// 		while (b->infile[i])
// 		{
// 			printf("AQUI\n");
// 			b->fd_in = open(b->infile[i], O_RDONLY);
// 			if (b->fd_in == -1)
// 				perror("ERROR");
// 			i++;
// 		}
// 		i = 0;
// 		while (b->outfile[i])
// 		{
// 			printf("AQUI\n");
// 			if (b->double_out[i] == 0)
// 				b->fd_out = open(b->outfile[i],
// 						O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			else if (b->double_out[i] == 1)
// 				b->fd_out = open(b->outfile[i],
// 						O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (b->fd_out == -1)
// 				perror("ERROR FILE OUTFILE");
// 			i++;
// 		}
// 		printf("este es el fd de entrada: %d\n", b->fd_in);
// 		// printf("este es el fd de salida: %d\n", b->fd_out);
// 		b++;
// 	}
// }

// void	take_fd(t_command *b)
// {
// 	while (b->last != 1)
// 	{
// 		if (b->infile != NULL)
// 		{
// 			b->fd_in = open(b->infile, O_RDONLY);
// 		}
// 		if (b->outfile != NULL)
// 		{
// 			if (b->double_out == 0)
// 			b->fd_out = open(b->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			else if (b->double_out == 1)
// 			b->fd_out = open(b->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		}
// 		printf("este es el fd de entrada: %d\n", b->fd_in);
// 		printf("este es el fd de salida: %d\n", b->fd_out);
// 		b++;
// 	}
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