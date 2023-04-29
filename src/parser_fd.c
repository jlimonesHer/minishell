/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriga <abarriga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:20:15 by abarriga          #+#    #+#             */
/*   Updated: 2023/04/29 14:20:16 by abarriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	take_fd(t_command *b)
{
	int	i;
	int	j;

	while (b->last != 1)
	{
		i = -1;
		j = 0;
		while (b->infile[++i])
		{
			if (open_infile(b, i, &j) == 1)
				return (perror("Error"), 1);
		}
		i = -1;
		while (b->outfile[++i])
		{
			open_outfile(b, i);
			if (b->fd_out == -1)
				return (perror("Error en fd de salida"), 1);
		}
		b++;
	}
	return (0);
}

void	open_outfile(t_command *b, int i)
{
	if (b->fd_out != 0)
		close(b->fd_out);
	if (b->double_out[i] == 0)
		b->fd_out = open(b->outfile[i],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (b->double_out[i] == 1)
		b->fd_out = open(b->outfile[i],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
}

int	open_infile(t_command *b, int i, int *j)
{
	if (b->fd_in != 0)
		close(b->fd_in);
	if (b->double_in[i] == 0)
	{
		b->fd_in = open(b->infile[i], O_RDONLY);
		if (b->fd_in == -1)
			return (1);
	}
	else if (b->double_in[i] == 1)
		b->delimiter[(*j)++] = b->infile[i];
	return (0);
}
