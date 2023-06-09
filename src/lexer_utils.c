/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriga <abarriga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:20:11 by abarriga          #+#    #+#             */
/*   Updated: 2023/04/29 14:20:12 by abarriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (words == -1)
	{
		while (tab[++words])
			;
	}
	while (i < words)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}
