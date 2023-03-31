#include "../includes/minishell.h"

int	count_quote_word(char *s, char quote)
{
	int	pos;

	pos = 1;
	while (s[pos] != quote && s[pos])
		pos++;
	return (pos);
}

int	check_doubleredir(char *s)
{
	if (*s == '>' || *s == '<')
		if (s[0] == s[1])
			return (2);
	return (1);
}

int	check_word(char *s)
{
	int	pos;

	pos = 0;
	if (ft_issame(*s, "<>|"))
	{
		pos += check_doubleredir(s);
		return (pos);
	}
	while (s[pos] && !ft_issame(s[pos], " ><|"))
	{
		if (ft_issame(s[pos], "\"\'"))
			pos += count_quote_word(&s[pos], s[pos]);
		pos++;
	}
	return (pos);
}

int	count_words(char *s)
{
	int	c_words;

	if (!s)
		return (0);
	c_words = 0;
	while (*s && *s == ' ')
		s++;
	while (*s)
	{
		s += check_word(s);
		s += ft_issame(*s, " ");
		c_words++;
	}
	return (c_words);
}

int	fill_cmd(char *input, int num_words, char **strs)
{
	int	word_len;
	int	i;
	int	j;

	i = 0;
	while (num_words > i)
	{
		input += ft_issame(*input, " ");
		word_len = check_word(input);
		strs[i] = ft_calloc(word_len + 1, sizeof(char));
		if (!strs[i])
			return (ft_freewords(i, strs), 0);
		j = 0;
		while (word_len > j)
		{
			strs[i][j] = input[j];
			j++;
		}
		input += word_len;
		i++;
	}
	return (0);
}

int check_redir(char **strs)
{
	if (!strs[0])
		return (0);
	if (ft_issame(strs[0][0], "<>|"))
		return (1);
	strs++;
	while (*strs)
	{
		if ((ft_issame(strs[-1][0], "<>") && ft_issame(strs[0][0], "<>|")) ||
			(ft_issame(strs[0][0], "<>|") && !strs[1]))
			return (1);
		strs++;
	}
	return (0);
}

char	**split_shell(char *input)
{
	char	**strs;
	int		num_words;

	num_words = count_words(input);
	strs = (char **)ft_calloc(num_words + 1, sizeof(char *));
	if (!strs || fill_cmd(input, num_words, strs))
		return (perror("Error"), NULL);
	if (check_redir(strs))
		return (ft_freewords(num_words, strs),ft_putendl_fd("Error:Parsing have a error.", 2) , NULL);
	return (strs);
}

char	**ft_freewords(int words, char **tab)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}