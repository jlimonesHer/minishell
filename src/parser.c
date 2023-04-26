#include "../includes/minishell.h"

t_command	*parser(char *input, char **envp)
{
	t_command	*b;
	int			n_cmds;
	char		**split_input;

	split_input = lexer(input);
	if (split_input == NULL)
		return (ft_putstr_fd("Error: invalid quotes\n", 2), NULL);
	n_cmds = count_cmds(split_input);
	b = ft_calloc(sizeof(t_command), (n_cmds + 1));
	if (!b)
		return (perror("Error"), NULL);
	b->n_cmds = n_cmds;
	last_cmd_table(b, b->n_cmds);
	fill_cmds(b, split_input);
	create_delimiter(b);
	if (take_fd(b))
		return (NULL);
	expand(b, envp);
	ft_freewords(-1, split_input);
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

			int i;
			int j = 0;
			while (!b[j].last)
			{
				printf("Comando %d\n", j);
				i = 0;
				while (b[j].argv && b[j].argv[i])
				{
					printf("%s\n", b[j].argv[i]);
					i++;
				}
				j++;
			}
		}
		// b[var.cmd].argv[var.j] = NULL;
		if (split_input[var.i] && (ft_issame(split_input[var.i][0], "|")))
		{
			var.i++;
			var.cmd++;
		}
	}
}

void	create_cmd(t_command *b, char	**split_input, t_fill *var)
{
	// printf("entrada deb create_cmd = %s\n", b[var->cmd].argv[var->j]);
	// printf("despues deb create_cmd = %s\n", split_input[var->i]);
	b[var->cmd].argv[var->j++] = ft_strdup(split_input[var->i++]);
	// printf("var %i \n", var->j);
	// var->j = var->j + 1;
	// var->i = var->i + 1;
	// printf("create_cmd = %s\n", split_input[var->i - 1]);
	b[var->cmd].argv[var->j] = NULL;
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
