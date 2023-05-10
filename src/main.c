/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlimones <jlimones@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:20:00 by abarriga          #+#    #+#             */
/*   Updated: 2023/05/10 12:02:19 by jlimones         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/stat.h>

void	main2(int si, char **va_export, char **env);

int	main(int argc, char **argv, char **envp)
{
	char		**env;
	char		**va_export;
	int			si;

	si = 1;
	(void)argc;
	(void)argv;
	va_export = env_copy2(envp);
	env = env_copy2(envp);
	main2(si, va_export, env);
	return (0);
}

void	main2(int si, char **va_export, char **env)
{
	t_command	*a;
	char		*input;

	while (si)
	{
		signal(SIGINT, ft_signal);
		input = readline("> ");
		if (!input)
			si = ctrl_d(input);
		else
		{
			if (input[0] == '\0' || count_words(input) == 0)
			{
				free(input);
				continue ;
			}
			else
				add_history(input);
			a = parser(input, env);
			if (a == NULL)
				continue ;
			executor(a, &env, &va_export);
			ft_free_struct(a, input);
			system("leaks minishell");
		}
	}
}

void	ft_free_struct(t_command	*a, char *input)
{
	int	i;

	i = 0;
	free(input);
	while (a[i].last != 1)
	{
		ft_freewords(-1, a[i].argv);
		if (a[i].infile)
			ft_freewords(-1, a[i].infile);
		if (a[i].outfile)
			ft_freewords(-1, a[i].outfile);
		if (a[i].delimiter)
			free(a[i].delimiter);
		if (a[i].double_out)
			free(a[i].double_out);
		if (a[i].double_in)
			free(a[i].double_in);
		i++;
	}
	free(a);
}
