#include "../includes/minishell.h"

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