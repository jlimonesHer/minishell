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
	int	cmd;
	int	pos;
	int	j;
	int	i;

	cmd = 0;
	i = 0;
	while (split_input[i])
	{
		pos = i;
		while (split_input[i] && !ft_issame(split_input[i][0], "|<>"))
			i++;
		b[cmd].argv = ft_calloc(sizeof(char *), i + 1);
		j = 0;
		while (pos < i)
			b[cmd].argv[j++] = ft_strdup(split_input[pos++]);
		cmd++;
		if (split_input[i] && ft_issame(split_input[i][0], "|"))
			i++;
	}
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