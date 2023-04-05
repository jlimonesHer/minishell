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

// typedef struct s_command {
// 	int		n_cmds;
// 	char	**split_input;
// }			t_command;

typedef struct s_command {
	char		**argv;
	char		*infile;
	int			double_ins;
	char		*outfile;
	int			double_out;
	int			last;
}				t_command;

typedef struct s_fill {
	int	cmd;
	int	pos;
	int	j;
	int	i;
	int	a;
	int	final;
	int	redir_in;
	int	redir_out;
}				t_fill;

/* utils.c */
void	ft_exit(char *cmd);



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

/*parser.c*/
int		count_cmds(char **split_input);
void	last_cmd_table(t_command *b, int n_cmds);
void	fill_cmds(t_command *b, char **split_input);
void	create_cmds(t_command *b, char	**split_input, t_fill *var);

#endif