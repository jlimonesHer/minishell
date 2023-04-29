/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriga <abarriga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:20:08 by abarriga          #+#    #+#             */
/*   Updated: 2023/04/29 14:20:09 by abarriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_input_quotes(char *input)
{
	char	quote;

	quote = '\0';
	while (*input)
	{
		if (*input == quote)
			quote = '\0';
		else if (ft_issame(*input, "\"\'") && quote == '\0')
			quote = *input;
		input++;
	}
	if (quote != '\0')
		return (1);
	return (0);
}

/**
 * @brief Función que hace un split a la entrada
 * 
 * @param input 
 * @return char** 
 */

char	**lexer(char *input)
{
	char	**split_input;

	if (check_input_quotes(input))
		return (NULL);
	split_input = split_shell(input);
	return (split_input);
}

/**
 * @brief Esta función te devuelve okey si encuentra el caracter en una cadena 
 * que le mandas a buscar
 * 
 * @param c 
 * @param str 
 * @return int 
 */

int	ft_issame(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}
