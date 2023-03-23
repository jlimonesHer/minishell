#include "../includes/minishell.h"

/**
 * @brief Esta funcion mira la entrada y verifica que haya si hay comillas o
 *  comilla sea en una cantidad par
 * 
 * @param input 
 * @return int 
 */
int	check_input_quotes(char *input)
{
	int	quotes;
	int	quote;
	int	flag_quotes;
	int	flag_quote;
	int	i;

	i = 0;
	quotes = 0;
	quote = 0;
	flag_quotes = 0;
	flag_quote = 0;
	while (input[i])
	{
		if (input[i] == '\"')
		{
			if (flag_quote == 1)
				return (1);
			quotes += 1;
			if (flag_quotes == 0)
				flag_quotes = 1;
			else if (flag_quotes == 1)
				flag_quotes = 0;
		}
		if (input[i] == '\'')
		{
			if (flag_quotes == 1)
				return (1);
			quote += 1;
			if (flag_quote == 0)
				flag_quote = 1;
			else if (flag_quote == 1)
				flag_quote = 0;
		}
		i++;
	}
	if (quotes % 2 == 0 && quote % 2 == 0)
		return (0);
	else
		return (1);
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
	{
		printf("ERROR");
		return (NULL);
	}
	split_input = ft_split(input, ' ');
	if (!split_input)
		return (NULL);
	return (split_input);
}