#include "../includes/minishell.h"

void	count_redir(char	**split_input, t_fill *var, t_command *b)
{
	int	i;
	int	cmd;
	int	j;

	i = 0;
	cmd = 0;
	while (split_input[i])
	{
		
		j = 0;
		var->c_in = 0;
		var->c_out = 0;
		while (split_input[i] && !ft_issame(split_input[i][0], "|"))
		{
			if (ft_issame(split_input[i][0], "<"))
				var->c_in += 1;
			else if (ft_issame(split_input[i][0], ">"))
				var->c_out += 1;
			else 
				j += 1;
			i++;
		}
		b[cmd].infile = ft_calloc(var->c_in + 1, sizeof(char *));
		b[cmd].double_in = ft_calloc(var->c_in + 1, sizeof(int));
		b[cmd].outfile = ft_calloc(var->c_out + 1, sizeof(char *));
		b[cmd].double_out = ft_calloc(var->c_out + 1, sizeof(int));
		b[cmd].argv = ft_calloc(sizeof(char *), j + 1);
		if (split_input[i] && (ft_issame(split_input[i][0], "|")))
		{
			i++;
			cmd++;
		}
	}
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
		while (b[cmd].double_in[++i])
			count += b[cmd].double_in[i];
		if (count > 0)
			b[cmd].delimiter = ft_calloc(count + 1, sizeof(char *));
		else
			b[cmd].delimiter = NULL;
		cmd++;
	}
}
