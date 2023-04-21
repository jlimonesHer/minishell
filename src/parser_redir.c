#include "../includes/minishell.h"

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
	if (var->c_in >= 0)
	{
		b[var->cmd].infile = ft_calloc(var->c_in + 1, sizeof(char *));
		b[var->cmd].double_in = ft_calloc(var->c_in + 1, sizeof(int));
	}
	if (var->c_out >= 0)
	{
		b[var->cmd].outfile = ft_calloc(var->c_out + 1, sizeof(char *));
		b[var->cmd].double_out = ft_calloc(var->c_out + 1, sizeof(int));
	}
	b[var->cmd].argv = ft_calloc(sizeof(char *),
			i - (2 * (var->c_in + var->c_out)) + 1);
}

void	create_infile(t_command *b, char **split_input, t_fill *var)
{
	b[var->cmd].infile[var->num_r_in] = ft_strdup(split_input[var->i + 1]);
	// printf("este es el infile %s\n", b[var->cmd].infile[var->num_r_in]);
	if (split_input[var->i][1])
		b[var->cmd].double_in[var->num_r_in] = 1;
	else
		b[var->cmd].double_in[var->num_r_in] = 0;
	var->num_r_in += 1;
	var->i += 2;
}

void	create_outfile(t_command *b, char **split_input, t_fill *var)
{
	b[var->cmd].outfile[var->num_r_out] = ft_strdup(split_input[var->i + 1]);
	// printf("este es el outfile %s\n", b[var->cmd].outfile[var->num_r_out]);
	if (split_input[var->i][1])
		b[var->cmd].double_out[var->num_r_out] = 1;
	else
		b[var->cmd].double_out[var->num_r_out] = 0;
	var->num_r_out += 1;
	var->i += 2;
}

void	create_delimiter(t_command *b)
{
	int	count;
	int	i;
	int	cmd;

	cmd = 0;
	while (b[cmd].last != 1)
	{
		count = 0;
		i = -1;
		while (b->double_in[++i])
			count += b->double_in[i];
		if (count > 0)
			b[cmd].delimiter = ft_calloc(count + 1, sizeof(char *));
		cmd++;
	}
}