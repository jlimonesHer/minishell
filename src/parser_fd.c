#include "../includes/minishell.h"

void	take_fd(t_command *b)
{
	int	i;

	while (b->last != 1)
	{
		i = -1;
		while (b->infile[++i])
		{
			if (b->fd_in != 0)
				close(b->fd_in);
			b->fd_in = open(b->infile[i], O_RDONLY);
			if (b->fd_in == -1)
				perror("ERROR");
		}
		i = -1;
		while (b->outfile[++i])
		{
			if (b->fd_out != 0)
				close(b->fd_out);
			if (b->double_out[i] == 0)
				b->fd_out = open(b->outfile[i],
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (b->double_out[i] == 1)
				b->fd_out = open(b->outfile[i],
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (b->fd_out == -1)
				perror("ERROR FILE OUTFILE");
		}
		b++;
	}
}