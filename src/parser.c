#include "../includes/minishell.h"

t_cmd_table parser(char *input)
{
	t_command   a;
	t_cmd_table	*b;
	int			n_cmds;

	a.argv = lexer(input);
	//comprobar la creacion del char** ha sido correcta
	n_cmds = count_cmds(a.argv);
	b = malloc(sizeof(t_cmd_table) * (n_cmds + 1));

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