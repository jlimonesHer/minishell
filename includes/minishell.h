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

typedef struct s_cmd_table {
	int		n_cmds;
}			t_cmd_table;

typedef struct s_command {
	char		**argv;
	char		**infile;
	int			fd_in;
	char		**outfile;
	int			fd_out;
	int			*double_out;
	int			last;
}				t_command;

// typedef struct s_cmd_table
// {
// 	int			n_cmds;
// 	t_command	*cmds;
// 	char		*infile;
// 	char		*outfile;
// }	t_cmd_table;

typedef struct s_fd_pipes
{
	int		fdin;
	int		fdout;
	int		tmpin;
	int		tmpout;
}	t_fd_pipes;

typedef struct s_fill {
	int	cmd;
	int	pos;
	int	j;
	int	i;
	int	a;
	int	final;
	int	redir_in;
	int	c_in;
	int	redir_out;
	int	c_out;
	int	num_r_in;
	int	num_r_out;
}			t_fill;

typedef struct s_expand {
	int		i;
	int		j;
	int		bg;
	char	*var;
}				t_expand;

/* utils.c */
void		ft_exit(char *cmd);

/*lexer.c*/
int			check_input_quotes(char *input);
char		**lexer(char *input);
int			ft_issame(char c, char *str);

/*split_shell.c*/
int			check_word(char *s);
int			count_words(char *s);
int			fill_cmd(char *input, int num_words, char **strs);
int			check_redir(char **strs);
char		**split_shell(char *input);

/*lexer_utils.c*/
int			count_quote_word(char *s, char quote);
int			check_doubleredir(char *s);
char		**ft_freewords(int words, char **tab);

/*parser.c*/
t_command	*parser(char *input);
int			count_cmds(char **split_input);
void		last_cmd_table(t_command *b, int n_cmds);
void		fill_cmds(t_command *b, char **split_input);
void		create_cmd(t_command *b, char	**split_input, t_fill *var);
void		count_redir(char	**split_input, t_fill *var, t_command *b);
void		create_infile(t_command *b, char **split_input, t_fill *var);
void		create_outfile(t_command *b, char **split_input, t_fill *var);
void		take_fd(t_command *b);
void		expand_quotes(t_command *b);

/*path_cmd.c*/
char		*search_path(char **envp, char *cmd);
void		ft_one_cmd(t_cmd_table *cmds, char **env);

/*builtin.c*/
void		ft_pwd(void);
//void	ft_echo(char *argv);
int			exec_builtin(char **argv, char **env);
#endif