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
	int	i;

	i = 0;
	quotes = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\"')
			quotes += 1;
		if (input[i] == '\'')
			quote += 1;
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