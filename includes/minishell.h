#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/wait.h>

typedef struct s_command {
	int		argc;
	char	**argv;
}			t_comand;

typedef struct s_cmd_table
{

}	t_cmd_table;

/* utils.c */
void	ft_exit(char *cmd);


#endif