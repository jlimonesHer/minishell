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