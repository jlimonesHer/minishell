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
	char		**argv;
	char		**infile;
	int			fd_in;
	int			*double_in;
	char		**delimiter;
	char		**outfile;
	int			fd_out;
	int			*double_out;
	int			n_cmds;
	int			last;
}				t_command;

typedef struct s_fd_pipes
{
	int		fdin;
	int		fdout;
	int		tmpin;
	int		tmpout;
	int		i;
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
	int		first;
	char	*var;
	char	*env;
	char	*line;
	char	*sub;
	char	*join;
}				t_expand;

/* utils.c */
void		ft_exit(t_command *cmds);
void		ft_free_struct(t_command	*a);
void		free_quotes(t_expand *e);
void		free_first_quotes(t_expand *e);
void		free_env(char **env);

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
t_command	*parser(char *input, char **envp);
int			count_cmds(char **split_input);
void		last_cmd_table(t_command *b, int n_cmds);
void		fill_cmds(t_command *b, char **split_input);
void		create_cmd(t_command *b, char	**split_input, t_fill *var);

/*parser_quotes.c*/
void		count_redir(char	**split_input, t_fill *var, t_command *b);
void		create_infile(t_command *b, char **split_input, t_fill *var);
void		create_outfile(t_command *b, char **split_input, t_fill *var);
void		create_delimiter(t_command *b);

/*path_cmd.c*/
char		*search_path(char **envp, char *cmd);
void		executor(t_command *cmds, char ***env, char ***var_export);

/*builtin.c*/
void		ft_pwd(void);
void		ft_env(char **envp);
char		**env_copy1(char **env);
char		**env_copy2(char **env);
int			exec_builtin(char **argv, char ***env, char ***var_export);
void		ft_export(char *argv, char ***env, char ***var_export);
void		add_export(char ***envp, char *var_export);
void		get_va_env(char *key, char *argv, char ***env);
char		**ft_unset(char *argv, char ***env);
void		ft_change_va_report(char ***env, char ***va_export, int b);
int			ft_create_child(t_command *cmds, char ***env, char ***var_export);
int			is_delim(t_command *cmds);

/*parser_fd.c*/
int			take_fd(t_command *b);
void		open_outfile(t_command *b, int i);
int			open_infile(t_command *b, int i, int j);

/*parser_quotes.c*/
void		expand(t_command *b, char **envp);
char		*search_env(char *var, char **envp);
char		*expand_text(char *cmd, char **envp);
char		*remove_quote(char *cmd);
char		*expand_quotes(char *cmd, char **envp);

/*signals.c*/
void		ft_signal(int sig);
int			ctrl_c(char *input);
#endif 
