#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <unistd.h>
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
}			t_command;

typedef struct s_cmd_table
{
	int			n_cmds;
	t_command	*cmds;
	char		*infile;
	char		*outfile;
}	t_cmd_table;

// typedef struct s_quote
// {
// 	int	quotes;
// 	int	quote;
// 	int	flag_quotes;
// 	int	flag_quote;
// 	int	i;
// }	t_quote;
typedef struct s_fd_pipes
{
	int		fdin;
	int		fdout;
	int		tmpin;
	int		tmpout;
}	t_fd_pipes;

/* utils.c */
void	ft_exit(char *cmd);

/*path_cmd.c*/
char	*search_path(char **envp, char *cmd);
void	ft_one_cmd(t_cmd_table *cmds, char **env);

/*builtin.c*/
void	ft_pwd(void);
//void	ft_echo(char *argv);
int		exec_builtin(char **argv, char **env);

/*lexer.c*/
int		check_input_quotes(char *input);
char	**lexer(char *input);
int		ft_issame(char c, char *str);

/*split_shell.c*/

int			count_quote_word(char *s, char quote);
int			check_doubleredir(char *s);
int			check_word(char *s);
int			count_words(char *s);
int			fill_cmd(char *input, int num_words, char **strs);
int			check_redir(char **strs);
char		**split_shell(char *input);
char		**ft_freewords(int words, char **tab);





/*lexer_utils.c*/

#endif